#!/usr/bin/env bash
set -euo pipefail

export ARCH=arm64
NPROC=$(nproc)
JOBS="${JOBS:-$(( NPROC < 4 ? NPROC : 4 ))}"
LOG=build.log

info() { printf '\n\033[1;32m==> %s\033[0m\n' "$*"; }

# --- 检查工具链 ---
missing=0
for t in make clang ld.lld bc flex bison; do
	command -v "$t" >/dev/null 2>&1 || { echo "缺少: $t"; missing=1; }
done
if [ "$missing" = 1 ]; then
	echo
	echo "Termux:  pkg install -y make clang lld llvm binutils bc flex bison perl openssl libelf python3"
	echo "Ubuntu:  sudo apt install -y make clang lld llvm bc flex bison libssl-dev libelf-dev"
	exit 1
fi

# --- 配置 ---
info "生成配置"
make LLVM=1 gki_defconfig

for opt in LTO_CLANG CFI_CLANG SHADOW_CALL_STACK RANDSTRUCT MODULE_SIG_ALL DEBUG_INFO_BTF; do
	scripts/config --disable "$opt" || true
done
scripts/config --set-str SYSTEM_TRUSTED_KEYS ""
scripts/config --set-str SYSTEM_REVOCATION_KEYS ""

scripts/config --enable ARCH_MEDIATEK
scripts/config --enable SERIAL_8250
scripts/config --enable SERIAL_8250_CONSOLE
scripts/config --enable SERIAL_8250_MT6577
scripts/config --enable SERIAL_EARLYCON

make LLVM=1 olddefconfig

echo "--- 关键配置 ---"
grep -E "ARCH_MEDIATEK|SERIAL_8250_MT6577|SERIAL_EARLYCON|CMDLINE_FORCE" .config

# --- 编译 ---
info "开始编译，并行度 $JOBS"
make LLVM=1 -j"$JOBS" Image dtbs 2>&1 | tee "$LOG"

# --- 检查产物 ---
info "产物"
ls -lh arch/arm64/boot/Image
ls -lh arch/arm64/boot/dts/mediatek/mt6891-chopin.dtb
file arch/arm64/boot/Image
