# Copyright 2022 Wong Hoi Sing Edison <hswong3i@pantarei-design.com>
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

%global debug_package %{nil}

%global _lto_cflags %{?_lto_cflags} -ffat-lto-objects

Name: libtasn1
Epoch: 100
Version: 4.19.0
Release: 1%{?dist}
Summary: The ASN.1 library used in GNUTLS
License: LGPL-2.1-or-later
URL: https://github.com/gnutls/libtasn1/tags
Source0: %{name}_%{version}.orig.tar.gz
BuildRequires: autoconf
BuildRequires: automake
BuildRequires: bison
BuildRequires: gcc
BuildRequires: libtool
BuildRequires: make
BuildRequires: pkgconfig
%if 0%{?suse_version} > 1500 || 0%{?sle_version} > 150000
Requires: libtasn1-6
%endif

%description
A library that provides Abstract Syntax Notation One (ASN.1, as
specified by the X.680 ITU-T recommendation) parsing and structures
management, and Distinguished Encoding Rules (DER, as per X.690)
encoding and decoding functions.

%prep
%autosetup -T -c -n %{name}_%{version}-%{release}
tar -zx -f %{S:0} --strip-components=1 -C .

%build
%configure \
    --disable-doc \
    --disable-gtk-doc \
    --disable-silent-rules \
    --disable-static \
    --disable-valgrind-tests \
    --enable-shared
%make_build

%install
%make_build install DESTDIR=%{buildroot}
find %{buildroot} -type f -name '*.la' -exec rm -rf {} \;

%check

%if 0%{?suse_version} > 1500 || 0%{?sle_version} > 150000
%package -n libtasn1-6
Summary: ASN.1 parsing library

%description -n libtasn1-6
This is the ASN.1 library used by GNUTLS. Abstract Syntax Notation One
(ASN.1) is a standardized data description and serialization language.

%package -n libtasn1-devel
Summary: Files for development of applications which will use libtasn1
Requires: libtasn1-6 = %{epoch}:%{version}-%{release}
Requires: pkgconfig

%description -n libtasn1-devel
This package contains files for development of applications which will
use libtasn1.

%package -n libtasn1-tools
Summary: Some ASN.1 tools
Requires: libtasn1-6 = %{epoch}:%{version}-%{release}

%description -n libtasn1-tools
This package contains simple tools that can decode and encode ASN.1
data.

%post -n libtasn1-6 -p /sbin/ldconfig
%postun -n libtasn1-6 -p /sbin/ldconfig

%files
%license COPYING

%files -n libtasn1-6
%{_libdir}/*.so.*

%files -n libtasn1-devel
%{_includedir}/*
%{_libdir}/*.so
%{_libdir}/pkgconfig/libtasn1.pc

%files -n libtasn1-tools
%{_bindir}/*
%endif

%if !(0%{?suse_version} > 1500) && !(0%{?sle_version} > 150000)
%package -n libtasn1-devel
Summary: Files for development of applications which will use libtasn1
Requires: libtasn1 = %{epoch}:%{version}-%{release}
Requires: pkgconfig

%description -n libtasn1-devel
This package contains files for development of applications which will
use libtasn1.

%package -n libtasn1-tools
Summary: Some ASN.1 tools
Requires: libtasn1 = %{epoch}:%{version}-%{release}

%description -n libtasn1-tools
This package contains simple tools that can decode and encode ASN.1
data.

%post -p /sbin/ldconfig
%postun -p /sbin/ldconfig

%files
%license COPYING
%{_libdir}/*.so.*

%files -n libtasn1-devel
%{_includedir}/*
%{_libdir}/*.so
%{_libdir}/pkgconfig/libtasn1.pc

%files -n libtasn1-tools
%{_bindir}/*
%endif

%changelog
