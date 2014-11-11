#
# Copyright (C) 2014 Filippo Sallemi <fsallemi@nomadnt.com>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this file.  If not, see <http://www.gnu.org/licenses/>.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=iwget
PKG_VERSION:=0.2
PKG_RELEASE:=2

PKG_BUILD_DIR := $(BUILD_DIR)/$(PKG_NAME)

include $(INCLUDE_DIR)/package.mk

define Package/iwget/default
    SECTION:=net
    CATEGORY:=Network
    URL:=http://lab.nomadnt.com/
    MAINTAINER:=Filippo Sallemi <fsallemi@nomadnt.com>
endef

define Package/iwget
$(call Package/iwget/default)
    TITLE:=Abstract wireless information cli
    DEPENDS:=+libiwinfo
endef

define Package/iwget/description
	Smart tool to get wireless card informations.
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) ./src/* $(PKG_BUILD_DIR)/
endef

define Build/Configure
endef

TARGET_CFLAGS += \
    -I$(STAGING_DIR)/usr/include/libnl-tiny \
    -I$(STAGING_DIR)/usr/include \
    -D_GNU_SOURCE

MAKE_FLAGS += \
    FPIC="$(FPIC)" \
    CFLAGS="$(TARGET_CFLAGS)" \
    LDFLAGS="$(TARGET_LDFLAGS)"

define Package/iwget/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/iwget $(1)/usr/bin/iwget
endef

$(eval $(call BuildPackage,iwget))
