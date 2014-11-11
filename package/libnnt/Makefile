#
# Copyright (C) 2009-2014 Filippo Sallemi <fsallemi@nomadnt.com>
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

PKG_NAME:=libnnt
PKG_VERSION:=0.2
PKG_RELEASE:=0

PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)-$(PKG_VERSION)
PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=git://github.com/nomadnt/LibNNT.git
PKG_SOURCE_PROTO:=git
PKG_SOURCE_VERSION:=HEAD
PKG_SOURCE_SUBDIR:=$(PKG_NAME)-$(PKG_VERSION)
PKG_INSTALL:=1

include $(INCLUDE_DIR)/package.mk	

define Package/libnnt
  SECTION:=libs
  CATEGORY:=Libraries
  TITLE:=Nomad NT core library
  URL:=http://lab.nomadnt.com/project/libnnt
  MAINTAINER:=Filippo Sallemi <fsallemi@nomadnt.com>
#  DEPENDS:=+iwget
endef

define Package/libnnt/description
  General purpose Nomad NT Libraries.
endef

define Package/libnnt/config
	source "$(SOURCE)/Config.in"
endef

define Package/libnnt/install
	#$(INSTALL_DIR) $(1)/sbin
	#$(INSTALL_DIR) $(1)/lib/nnt

	#$(INSTALL_BIN) $(PKG_INSTALL_DIR)/valid $(1)/sbin
	$(CP) $(PKG_INSTALL_DIR)/* $(1)/
endef

$(eval $(call BuildPackage,libnnt))
