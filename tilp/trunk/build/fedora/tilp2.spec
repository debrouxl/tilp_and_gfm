Name: tilp2
Epoch: 1
Version: 1.08
Release: 2
Vendor: LPG (http://lpg.ticalc.org)
Packager: Kevin Kofler <Kevin@tigcc.ticalc.org>
# tarball respun to add pixmaps/*.png from SVN
Source: %{name}-%{version}.tar.bz2
#LANG=C svn diff -r 3859:3860 >../tilp2-1.08-install-png-files.diff
Patch0: tilp2-1.08-install-png-files.diff
#LANG=C svn diff -r 3870:3871 config.h.in >../tilp2-1.08-regen-config.h.in-autoheader.diff
Patch1: tilp2-1.08-regen-config.h.in-autoheader.diff
#LANG=C svn diff -r 3896:3897 >../tilp2-1.08-increase-flashapp-timeout.diff
Patch2: tilp2-1.08-increase-flashapp-timeout.diff
#LANG=C svn diff -r 3907:3909 >../tilp2-1.08-remember-filesel-native.diff
Patch3: tilp2-1.08-remember-filesel-native.diff
#LANG=C svn diff -r 3909:3910 >../tilp2-1.08-fix-kde-filesel.diff
Patch4: tilp2-1.08-fix-kde-filesel.diff
Group: Applications/Communications
License: GPL
BuildRequires: libticables2-devel >= 1:1.0.6, libticonv-devel >= 1:1.0.4, libtifiles2-devel >= 1:1.0.7, libticalcs2-devel >= 1:1.0.7, glib2-devel >= 2.6.0, gtk2-devel >= 2.6.0, libglade2-devel >= 2.4.0, zlib-devel, kdelibs-devel >= 6:3.0, desktop-file-utils >= 0.10
Requires: xdg-utils >= 1.0.0
BuildRoot: %{_tmppath}/%{name}-%{version}-%{release}-root-%(%{__id_u} -n)
Summary: TiLP is a TI<->PC linking program
Obsoletes: tilp < 20050828
%description
TiLP is a TI<->PC linking program

%prep
%setup
%patch0 -p0
%patch1 -p0
%patch2 -p0
%patch3 -p0
%patch4 -p0

%build
CFLAGS="$RPM_OPT_FLAGS" ./configure --prefix=%{_prefix} --libdir=%{_libdir} --mandir=%{_mandir} --disable-nls
make

%install
if [ -d $RPM_BUILD_ROOT ]; then rm -rf $RPM_BUILD_ROOT; fi
mkdir -p $RPM_BUILD_ROOT
make install DESTDIR=$RPM_BUILD_ROOT
mkdir -p ${RPM_BUILD_ROOT}/usr/share/applications
cat >${RPM_BUILD_ROOT}/usr/share/applications/tilp.desktop <<EOF
[Desktop Entry]
Name=TiLP
Name[fr_FR]=TiLP
Comment=Ti Linking Program
Comment[fr_FR]=Programme de connexion pour calculatrices TI
GenericName=TI Linking Program
GenericName[fr_FR]=Connexion calculatrices TI
Encoding=UTF-8
Version=1.0
Type=Application
Exec=/usr/bin/tilp
Icon=/usr/share/tilp2/pixmaps/icon.xpm
Terminal=false
Categories=Utility;X-KDE-Utilities-Peripherals;
MimeType=application/x-tilp
EOF
desktop-file-install --delete-original --vendor lpg     \
  --dir ${RPM_BUILD_ROOT}%{_datadir}/applications          \
  ${RPM_BUILD_ROOT}/usr/share/applications/tilp.desktop
mkdir -p ${RPM_BUILD_ROOT}%{_datadir}/mime/packages
cat >${RPM_BUILD_ROOT}%{_datadir}/mime/packages/tilp.xml <<EOF
<?xml version="1.0" encoding="UTF-8"?>
<mime-info xmlns="http://www.freedesktop.org/standards/shared-mime-info">
    <mime-type type="application/x-tilp">
        <comment xml:lang="en">TI File</comment>
        <comment xml:lang="fr">Fichier TI</comment>
        <glob pattern="*.73?" />
        <glob pattern="*.82?" />
        <glob pattern="*.8[xX]?" />
        <glob pattern="*.85?" />
        <glob pattern="*.86?" />
        <glob pattern="*.89?" />
        <glob pattern="*.92?" />
        <glob pattern="*.9[xX]?" />
        <glob pattern="*.[vV]2?" />
  </mime-type>
</mime-info>
EOF

%post
update-mime-database %{_datadir}/mime > /dev/null 2>&1 || :
update-desktop-database %{_datadir}/applications > /dev/null 2>&1 || :

%postun
update-mime-database %{_datadir}/mime > /dev/null 2>&1 || :
update-desktop-database %{_datadir}/applications > /dev/null 2>&1 || :

%clean
rm -rf $RPM_BUILD_ROOT

%files
%defattr(-, root, root)
/usr/bin/tilp
%{_mandir}/man1/tilp*
/usr/share/tilp2
%{_datadir}/applications/lpg-tilp.desktop
%{_datadir}/mime/packages/tilp.xml

%changelog
* Sun Oct 14 2007 Kevin Kofler <Kevin@tigcc.ticalc.org> 1:1.08-2
Backport increased FlashApp timeout from SVN.
Backport fix to not hardcode the file selector type in the config file from SVN.
Backport fix for the KDE file dialog (dirname+filename concatenation) from SVN.

* Sat Oct 13 2007 Kevin Kofler <Kevin@tigcc.ticalc.org> 1:1.08-1
Update to 1.08.
Backport fix to install .png icons from SVN.
Backport fix for WITH_KDE to make KDE support actually work from SVN.

* Sun Sep 2 2007 Kevin Kofler <Kevin@tigcc.ticalc.org> 1:1.07-1
Update to 1.07.

* Wed Jun 27 2007 Kevin Kofler <Kevin@tigcc.ticalc.org> 1:1.06-1
Update to 1.06.
Update tilibs BuildRequires.

* Wed May 16 2007 Kevin Kofler <Kevin@tigcc.ticalc.org>
Drop -n tilp, the tarball uses name-version format now.

* Mon Apr 16 2007 Kevin Kofler <Kevin@tigcc.ticalc.org> 1:1.04-1
Bump Epoch.
Use real version number instead of date.
Also use real version numbers and Epoch 1 for the dependencies.

* Mon Apr 16 2007 Kevin Kofler <Kevin@tigcc.ticalc.org>
Remove redundant explicit Requires.
Don't BuildRequire newer versions than actually needed.
Don't require desktop-file-utils and shared-mime-info for post and postun (not
needed in FC5+).

* Fri Apr 6 2007 Kevin Kofler <Kevin@tigcc.ticalc.org>
BuildRequire kdelibs-devel, Require kdelibs.

* Wed Feb 7 2007 Kevin Kofler <Kevin@tigcc.ticalc.org>
Require xdg-utils.

* Sun Nov 12 2006 Kevin Kofler <Kevin@tigcc.ticalc.org>
Drop tilp-2 -> tilp symlinks, as the executable is now named just tilp again.

* Thu Jul 20 2006 Kevin Kofler <Kevin@tigcc.ticalc.org>
Libdir fixes for lib64 platforms.
Use libtifoo-devel instead of libtifoo in BuildRequires.
Pass mandir explicitly so the manfile directory doesn't depend on the autoconf
version used to generate configure.

* Fri Jun 16 2006 Kevin Kofler <Kevin@tigcc.ticalc.org>
Remove redundant %%defattr at the end of %%files.

* Wed May 24 2006 Kevin Kofler <Kevin@tigcc.ticalc.org>
Make sure permissions are set correctly when building as non-root.
--enable-exit-homedir not needed anymore (now default).
Allow manpages to be gzipped (done by rpm when using redhat-rpm-config).
Add X-KDE-Utilities-Peripherals category to .desktop file.

* Mon May 22 2006 Kevin Kofler <Kevin@tigcc.ticalc.org>
Build debuginfo RPM.
Use the system-wide default RPM_OPT_FLAGS instead of my own.
Use BuildRoot recommended by the Fedora packaging guidelines.

* Sun May 7 2006 Kevin Kofler <Kevin@tigcc.ticalc.org>
Now requires libticonv.

* Sat Feb 11 2006 Kevin Kofler <Kevin@tigcc.ticalc.org>
Update setup -n to use the new directory name (tilp, not tilp2).

* Wed Jan 4 2006 Kevin Kofler <Kevin@tigcc.ticalc.org>
Change Vendor to LPG.

* Wed Sep 14 2005 Kevin Kofler <Kevin@tigcc.ticalc.org>
Update to TiLP 2: new package name, new dependencies, obsoletes the old package,
some files moved, some compatibility symlinks added, .desktop file updated for
new icon location, dropped obsolete
tilp-no-obsolete-desktop-and-mime-entries.diff patch.

* Mon Jun 20 2005 Kevin Kofler <Kevin@tigcc.ticalc.org>
Revert -Wl,--export-dynamic addition (now upstream).

* Sun Jun 19 2005 Kevin Kofler <Kevin@tigcc.ticalc.org>
Bump version requirements for FC4.
Change Copyright to License.
Add missing -Wl,--export-dynamic.

* Fri May 27 2005 Kevin Kofler <Kevin@tigcc.ticalc.org>
Add Requires on zlib and BuildRequires on zlib-devel.

* Fri May 6 2005 Kevin Kofler <Kevin@tigcc.ticalc.org>
Menu entry and MIME type support.

* Mon May 2 2005 Kevin Kofler <Kevin@tigcc.ticalc.org>
First Fedora RPM.
