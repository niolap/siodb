# Copyright (C) 2019-2020 Siodb GmbH. All rights reserved.
# Use of this source code is governed by a license that can be found
# in the LICENSE file.

# Global Makefile for Siodb

.PHONY: all clean full-clean tools common siodb conn_worker iomgr siocli restcli rest_server \
	clean-tools clean-common clean-siodb clean-conn_worker clean-iomgr clean-siocli clean-restcli \
	clean-rest_server help debug debug-no-ut release release-no-ut

all:
	@date
	$(MAKE) $@ -C common
	$(MAKE) $@ -C tools
	$(MAKE) $@ -C siodb
	$(MAKE) $@ -C conn_worker
	$(MAKE) $@ -C iomgr
	$(MAKE) $@ -C siocli
	$(MAKE) $@ -C restcli
	$(MAKE) $@ -C rest_server
	$(MAKE) $@ -C extra_files
	@date

debug:
	@date
	$(MAKE) all -C common
	$(MAKE) all -C tools
	$(MAKE) all -C siodb
	$(MAKE) all -C conn_worker
	$(MAKE) all -C iomgr
	$(MAKE) all -C siocli
	$(MAKE) all -C restcli
	$(MAKE) all -C rest_server
	$(MAKE) all -C extra_files
	@date

debug-no-ut:
	@date
	$(MAKE) BUILD_UNIT_TESTS=0 all -C common
	$(MAKE) BUILD_UNIT_TESTS=0 all -C tools
	$(MAKE) BUILD_UNIT_TESTS=0 all -C siodb
	$(MAKE) BUILD_UNIT_TESTS=0 all -C conn_worker
	$(MAKE) BUILD_UNIT_TESTS=0 all -C iomgr
	$(MAKE) BUILD_UNIT_TESTS=0 all -C siocli
	$(MAKE) BUILD_UNIT_TESTS=0 all -C restcli
	$(MAKE) BUILD_UNIT_TESTS=0 all -C rest_server
	$(MAKE) BUILD_UNIT_TESTS=0 all -C extra_files
	@date

release:
	@date
	$(MAKE) DEBUG=0 all -C common
	$(MAKE) DEBUG=0 all -C tools
	$(MAKE) DEBUG=0 all -C siodb
	$(MAKE) DEBUG=0 all -C conn_worker
	$(MAKE) DEBUG=0 all -C iomgr
	$(MAKE) DEBUG=0 all -C siocli
	$(MAKE) DEBUG=0 all -C restcli
	$(MAKE) DEBUG=0 all -C rest_server
	$(MAKE) DEBUG=0 all -C extra_files
	@date

release-no-ut:
	@date
	$(MAKE) DEBUG=0 BUILD_UNIT_TESTS=0 all -C common
	$(MAKE) DEBUG=0 BUILD_UNIT_TESTS=0 all -C tools
	$(MAKE) DEBUG=0 BUILD_UNIT_TESTS=0 all -C siodb
	$(MAKE) DEBUG=0 BUILD_UNIT_TESTS=0 all -C conn_worker
	$(MAKE) DEBUG=0 BUILD_UNIT_TESTS=0 all -C iomgr
	$(MAKE) DEBUG=0 BUILD_UNIT_TESTS=0 all -C siocli
	$(MAKE) DEBUG=0 BUILD_UNIT_TESTS=0 all -C restcli
	$(MAKE) DEBUG=0 BUILD_UNIT_TESTS=0 all -C rest_server
	$(MAKE) DEBUG=0 BUILD_UNIT_TESTS=0 all -C extra_files
	@date

clean:
	@date
	$(MAKE) $@ -C common
	$(MAKE) $@ -C tools
	$(MAKE) $@ -C siodb
	$(MAKE) $@ -C conn_worker
	$(MAKE) $@ -C iomgr
	$(MAKE) $@ -C siocli
	$(MAKE) $@ -C restcli
	$(MAKE) $@ -C rest_server
	$(MAKE) $@ -C extra_files
	@date

full-clean:
	@date
	$(MAKE) $@ -C siodb
	@date

check-headers:
	@date
	$(MAKE) $@ -C common
	$(MAKE) $@ -C tools
	$(MAKE) $@ -C siodb
	$(MAKE) $@ -C conn_worker
	$(MAKE) $@ -C iomgr
	$(MAKE) $@ -C siocli
	$(MAKE) $@ -C restcli
	$(MAKE) $@ -C rest_server
	$(MAKE) $@ -C restcli
	@date

check-headers-debug:
	@date
	$(MAKE) check-headers DEBUG=1 -C common
	$(MAKE) check-headers DEBUG=1 -C tools
	$(MAKE) check-headers DEBUG=1 -C siodb
	$(MAKE) check-headers DEBUG=1 -C conn_worker
	$(MAKE) check-headers DEBUG=1 -C iomgr
	$(MAKE) check-headers DEBUG=1 -C siocli
	$(MAKE) check-headers DEBUG=1 -C restcli
	$(MAKE) check-headers DEBUG=1 -C rest_server
	$(MAKE) check-headers DEBUG=1 -C restcli
	@date

check-headers-release:
	@date
	$(MAKE) check-headers DEBUG=0 -C common
	$(MAKE) check-headers DEBUG=0 -C tools
	$(MAKE) check-headers DEBUG=0 -C siodb
	$(MAKE) check-headers DEBUG=0 -C conn_worker
	$(MAKE) check-headers DEBUG=0 -C iomgr
	$(MAKE) check-headers DEBUG=0 -C siocli
	$(MAKE) check-headers DEBUG=0 -C restcli
	$(MAKE) check-headers DEBUG=0 -C rest_server
	$(MAKE) check-headers DEBUG=0 -C restcli
	@date

common:
	@date
	$(MAKE) -C $@
	@date

tools:
	@date
	$(MAKE) -C $@
	@date

siodb:
	@date
	$(MAKE) -C $@
	@date

conn_worker:
	@date
	$(MAKE) -C $@
	@date

iomgr:
	@date
	$(MAKE) -C $@
	@date

siocli:
	@date
	$(MAKE) -C $@
	@date

restcli:
	@date
	$(MAKE) -C $@
	@date

rest_server:
	@date
	$(MAKE) -C rest_server
	@date

extra_files:
	@date
	$(MAKE) -C $@
	@date

clean-tools:
	@date
	$(MAKE) clean -C $(subst clean-,,$@)
	@date

clean-common:
	@date
	$(MAKE) clean -C $(subst clean-,,$@)
	@date

clean-siodb:
	@date
	$(MAKE) clean -C $(subst clean-,,$@)
	@date

clean-conn_worker:
	@date
	$(MAKE) clean -C $(subst clean-,,$@)
	@date

clean-iomgr:
	@date
	$(MAKE) clean -C $(subst clean-,,$@)
	@date

clean-siocli:
	$(MAKE) clean -C $(subst clean-,,$@)
	@date

clean-restcli:
	$(MAKE) clean -C $(subst clean-,,$@)
	@date

clean-rest_server:
	@date
	$(MAKE) clean -C rest_server
	@date

clean-extra_files:
	$(MAKE) clean -C $(subst clean-,,$@)
	@date

include mk/Help.mk
