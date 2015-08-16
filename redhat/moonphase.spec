%define MmVersion 0.3
Name:           moonphase
Version:        %{MmVersion}.1
Release:        1
Summary:        Displays the phase of the moon in the system tray

License:        GPLv3+
URL:            http://sourceforge.net/projects/moonphase/
Source0:        http://sourceforge.net/projects/moonphase/files/%{MmVersion}/moonphase-%{version}.tar.gz

%description
Displays the phase of the moon in the system tray. Additionally, a window
 can be displayed that shows user selectable data about the moon
 (rise/set times, percent illumination, etc).

BuildRequires:  
Requires:       

%changelog
* Sun Aug 16 2015 Alan Wise <alanwise@users.sourceforge.net> - 0.3.1-1
- New upstream version.

* Tue Oct 14 2014 Alan Wise <alanwise@users.sourceforge.net> - 0.2.3-1
- New upstream version.

* Thu Sep 4 2014 Alan Wise <alanwise@users.sourceforge.net> - 0.2.2-1
- New upstream version.
- Minor spec changes.
- Added desktop entry.

* Thu Jul 31 2014 Alan Wise <alanwise@users.sourceforge.net> - 0.2.1-1
- New upstream version.

* Thu Jul 31 2014 Alan Wise <alanwise@users.sourceforge.net> - 0.2.0-1
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
%{_bindir}/%{name}-qt
%{_datadir}/%{name}/moon_56frames.png
%{_datadir}/icons/%{name}.xpm
%{_datadir}/applications/%{name}-qt.desktop
%doc COPYING

#ExcludeArch:
#Excludeos:
