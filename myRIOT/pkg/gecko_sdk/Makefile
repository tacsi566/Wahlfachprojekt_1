PKG_NAME=gecko_sdk
PKG_URL=https://github.com/basilfx/RIOT-gecko-sdk
PKG_VERSION=944639a57adce84fb110fe89e54f50e161607918
PKG_LICENSE=Zlib

include $(RIOTBASE)/pkg/pkg.mk

ifneq ($(CPU),efm32)
  $(error This package can only be used with EFM32 CPUs)
endif

ifneq (llvm,$(TOOLCHAIN))
  CFLAGS += -Wno-int-in-bool-context
endif

# Disable -Wcast-align for this package, as source contains cast that increase
# alignment requirements. Let's hope those are false positives and proper
# alignment is assured.
CFLAGS += -Wno-cast-align

all:
	$(QQ)"$(MAKE)" -C $(PKG_SOURCE_DIR)/dist
