Name:           range
Version:        0.0.1
Release:        alt1
Summary:        Arithmetic progression generator
License:        MIT
Group:          Other
Url:            https://uneex.org/LecturesCMC/LinuxApplicationDevelopment2026/05_Debugging
Packager:       Maksim Kunts <private@mail.com>

Source:         %name-%version.tar.gz
BuildRequires:  gcc
BuildRequires:  make
BuildRequires:  gdb

%description

The program prints sequence of numbers: 
* [0, stop), or 
* [start, stop), or
* {x: x = start+i*step} between start and stop not including stop,
one element per line.

%prep
%setup

%build
make all

%install
mkdir -p %buildroot%_bindir
install -Dpm 0755 range %buildroot%_bindir/%name

%files
%_bindir/%name

%changelog
* Mon Oct 19 2026 Maksim Kunts <private@mail.com> 0.0.1-alt1
- Initial build