AT24_POC_VERSION = 1.0
AT24_POC_SITE = package/at24_poc/src
#AT24_POC_SITE = at24_poc
AT24_POC_SITE_METHOD = local
AT24_POC_SOURCE = at24_poc.c

define AT24_POC_BUILD_CMDS
    $(TARGET_MAKE_ENV) $(MAKE) -C $(@D) CROSS_COMPILE=$(TARGET_CROSS)
endef

define AT24_POC_INSTALL_TARGET_CMDS
    $(INSTALL) -D -m 0755 $(@D)/at24_poc $(TARGET_DIR)/usr/bin/at24_poc
endef




$(eval $(generic-package))
