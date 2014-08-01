Name:           moonphase
Version:        0.2.1
Release:        1
Summary:        Displays the phase of the moon in the system tray

License:        GPLv3+
URL:            http://moonphase.sourceforge.net
Source0:        http://sourceforge.net/projects/moonphase/files/${version}/moonphase-%{version}.tar.gz

%description
Displays the phase of the moon in the system tray. Additionally, a window
 can be displayed that shows user selectable data about the moon
 (rise/set times, percent illumination, etc).

BuildRequires:  
Requires:       

%changelog
* Thu Jul 31 2014 Alan Wise <alanwise@sourceforge.net> - 0.2.1-1
- New upstream version.

* Thu Jul 31 2014 Alan Wise <alanwise@sourceforge.net> - 0.2.0-1
- Initial version of the package.

Group: Applications/Engineering
Prefix: /usr
Provides: moonphase

%prep
%setup -q
cmake -DCMAKE_BUILD_TYPE:STRING="Release" -DCMAKE_INSTALL_PREFIX:STRING="/usr"

%build
make

%install
%make_install

%files
%defattr(-,root,root,-)
%{_bindir}/moonphase-qt
%{_datadir}/%{name}/moon_56frames.png
%{_datadir}/pixmaps/moonphase.xpm
%doc COPYING

#ExcludeArch:
#Excludeos:
