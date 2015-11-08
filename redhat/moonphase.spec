%define MmVersion 0.3
Name:           moonphase
Version:        %{MmVersion}.2
Release:        1
Summary:        No summary
License:        GPLv3+
URL:            http://sourceforge.net/projects/moonphase/
Source0:        http://sourceforge.net/projects/moonphase/files/%{MmVersion}/moonphase-%{version}.tar.gz

%description
No description.

%package qt
Summary: Qt version of moonphase

%description qt
Displays the phase of the moon in the system tray. Additionally, a window
 can be displayed that shows user selectable data about the moon
 (rise/set times, percent illumination, etc).

%files qt
%defattr(-,root,root,-)
%{_bindir}/%{name}-qt
%{_datadir}/%{name}-qt/moon_56frames.png
%{_datadir}/icons/%{name}-qt.xpm
%{_datadir}/applications/%{name}-qt.desktop
%doc COPYING

%changelog
* Wed Aug 19 2015 Alan Wise <alanwise@users.sourceforge.net> - 0.3.2-1
- New upstream version.

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
Provides: moonphase-qt

%prep
%setup -q
cmake -DCMAKE_BUILD_TYPE:STRING="Release" -DCMAKE_INSTALL_PREFIX:STRING="/usr"

%build
make

%install
%make_install

%preun qt
killall moonphase-qt
