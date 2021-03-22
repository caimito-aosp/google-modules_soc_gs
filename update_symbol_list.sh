#!/bin/bash
# SPDX-License-Identifier: GPL-2.0

# Add a trap to remove the temporary vmlinux in case of an error occurs before
# we finish.
cleanup_trap() {
  rm -f ${VMLINUX_TMP} ${TMP_LIST}
  exit $1
}
trap 'cleanup_trap' EXIT

# We need to update the AOSP symbol list by cat'ing the Pixel symbol list and
# the AOSP symbol list together so that we don't drop symbols that may have
# merged in AOSP before they were merged into the pixel tree.
#
# $1 pixel symbol list
# $2 aosp symbol list
function update_aosp_symbol_list {
  local pixel_symbol_list=$1
  local aosp_symbol_list=$2

  # Remove blank lines and comments. Then sort
  TMP_LIST=$(mktemp -t symbol_list.XXXX)
  cat ${pixel_symbol_list} ${aosp_symbol_list} > ${TMP_LIST}
  sed -i '/^$/d' ${TMP_LIST}
  sed -i '/^#/d' ${TMP_LIST}
  sort -u ${TMP_LIST} > ${aosp_symbol_list}

  rm -f ${TMP_LIST}
}

function extract_pixel_symbols {
  echo "========================================================"
  echo " Extracting symbols and updating the symbol list"
  local clang_prebuilt_bin=$(. private/gs-google/build.config.common && \
    echo $CLANG_PREBUILT_BIN)
  local pixel_symbol_list=$1

  # Need to copy over the vmlinux to be under the same directory as we point
  # extract_symbols to.
  cp ${DIST_DIR}/vmlinux ${VMLINUX_TMP}

  PATH=${PATH}:${clang_prebuilt_bin}
  build/abi/extract_symbols              \
      --symbol-list ${pixel_symbol_list} \
      --skip-module-grouping             \
      --additions-only                   \
      ${BASE_OUT}/device-kernel/private
  err=$?
  if [ "${err}" != "0" ]; then
    echo "ERROR: Failed to extract symbols! ret=${err}" >&2
    exit ${err}
  fi

  # Strip the core ABI symbols from the pixel symbol list
  grep "^ " aosp/android/abi_gki_aarch64_core | while read l; do
    sed -i "/\<$l\>/d" ${pixel_symbol_list}
  done

  # Remove blank lines and comments. Then sort
  TMP_LIST=$(mktemp -t symbol_list.XXXX)
  cp -f ${pixel_symbol_list} ${TMP_LIST}
  sed -i '/^$/d' ${TMP_LIST}
  sed -i '/^#/d' ${TMP_LIST}
  sort -u ${TMP_LIST} > ${pixel_symbol_list}

  # Clean up
  rm -f ${VMLINUX_TMP} ${TMP_LIST}
}

export SKIP_MRPROPER=1
export BASE_OUT=${OUT_DIR:-out}/mixed/
export DIST_DIR=${DIST_DIR:-${BASE_OUT}/dist/}
VMLINUX_TMP=${BASE_OUT}/device-kernel/private/vmlinux

BUILD_KERNEL=1 TRIM_NONLISTED_KMI=0 ENABLE_STRICT_KMI=0 ./build_slider.sh "$@"
err=$?
if [ "${err}" != "0" ]; then
  echo "ERROR: Failed to run ./build_slider.sh! ret=${err}" >&2
  exit 1
fi

extract_pixel_symbols "private/gs-google/android/abi_gki_aarch64_generic"
update_aosp_symbol_list "private/gs-google/android/abi_gki_aarch64_generic" \
  "aosp/android/abi_gki_aarch64_generic"

echo "========================================================"
echo " The symbol list has been update locally in aosp/ and private/gs-google."
echo " Compiling with BUILD_KERNEL=1 is now required until the new symbol(s)"
echo " are merged. Re-compile using the below command:"
echo
echo " SKIP_MRPROPER=1 BUILD_KERNEL=1 ./build_slider.sh"
echo