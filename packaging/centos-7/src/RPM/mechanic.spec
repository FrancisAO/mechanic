Name: mechanic
Version: 1
Release: 0
Summary: Simple server migration tool.
Source0: mechanic-sources.tar.gz
License: GNU General Public License, Version 3
Group: Tools
BuildArch: x86_64
BuildRoot: %{_tmppath}/%{name}-buildroot
%description
Simple server migration tool.
%prep
%build
%install
install -m 0755 -d $RPM_BUILD_ROOT/etc/mechanic
install -m 0755 -d $RPM_BUILD_ROOT/etc/mechanic/migration.d
install -m 0755 -d $RPM_BUILD_ROOT/usr/sbin/
install -m 0755 -d $RPM_BUILD_ROOT/usr/lib64/
install -m 0755 $RPM_BUILD_ROOT/../../BUILD/usr/bin/mechanic $RPM_BUILD_ROOT/usr/bin/mechanic 
install -m 0755 $RPM_BUILD_ROOT/../../BUILD/usr/lib64/libmechanic.so $RPM_BUILD_ROOT/usr/lib64/libmechanic.so
%clean
rm -rf $RPM_BUILD_ROOT
%post
%files
%dir /etc/mechanic
%dir /etc/mechanic/migration.d
/usr/bin/mechanic
/usr/lib64/libmechanic.so
