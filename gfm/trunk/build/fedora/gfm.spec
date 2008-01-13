Name: gfm
Version: 1.02
Release: 1
Vendor: LPG (http://lpg.ticalc.org)
Packager: Kevin Kofler <Kevin@tigcc.ticalc.org>
Source: %{name}-%{version}.tar.bz2
Group: Applications/Communications
License: GPLv2+
BuildRequires: libticonv-devel >= 1:1.0.4, libtifiles2-devel >= 1:1.0.7, libticalcs2-devel >= 1:1.0.7, glib2-devel >= 2.6.0, gtk2-devel >= 2.6.0, libglade2-devel >= 2.5.0, kdelibs3-devel, desktop-file-utils >= 0.10
BuildRoot: %{_tmppath}/%{name}-%{version}-%{release}-root-%(%{__id_u} -n)
Summary: Group File Manager
%description
GFM is a program allowing to create/open/save TI handheld files.
It can group & ungroup files, too.

%prep
%setup -q

%build
CFLAGS="$RPM_OPT_FLAGS" ./configure --prefix=%{_prefix} --libdir=%{_libdir} --mandir=%{_mandir} --disable-nls
make

%install
if [ -d $RPM_BUILD_ROOT ]; then rm -rf $RPM_BUILD_ROOT; fi
mkdir  $RPM_BUILD_ROOT
make install DESTDIR=$RPM_BUILD_ROOT
mkdir -p ${RPM_BUILD_ROOT}/usr/share/applications
cat >${RPM_BUILD_ROOT}/usr/share/applications/gfm.desktop <<EOF
[Desktop Entry]
Name=GFM
Comment=Group File Manager for TI calculators
GenericName=Group File Manager for TI calculators
Encoding=UTF-8
Version=1.0
Type=Application
Exec=/usr/bin/gfm
Icon=/usr/share/gfm/pixmaps/logo.xpm
Terminal=false
Categories=Utility;X-KDE-Utilities-Peripherals;
MimeType=application/x-tilp
EOF
desktop-file-install --delete-original --vendor lpg     \
  --dir ${RPM_BUILD_ROOT}%{_datadir}/applications          \
  ${RPM_BUILD_ROOT}/usr/share/applications/gfm.desktop

%post
update-desktop-database %{_datadir}/applications > /dev/null 2>&1 || :

%postun
update-desktop-database %{_datadir}/applications > /dev/null 2>&1 || :

%clean
rm -rf $RPM_BUILD_ROOT

%files
%defattr(-, root, root)
/usr/bin/gfm
%{_mandir}/man1/gfm*
/usr/share/gfm
%{_datadir}/applications/lpg-gfm.desktop

%changelog
* Sun Jan 13 2008 Kevin Kofler <Kevin@tigcc.ticalc.org> 1.02-1
Update to 1.02 (release).

* Sun Oct 14 2007 Kevin Kofler <Kevin@tigcc.ticalc.org> 1.02-0.1.20071014svn
First Fedora RPM.
