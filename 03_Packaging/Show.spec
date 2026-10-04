Name:           Show
Version:        0.0.1
Release:        alt1
Group:          Other
License:        MIT
URL:            https://uneex.org/LecturesCMC/LinuxApplicationDevelopment2026/03_Packaging
Source:         %name-%version.tar.gz
Summary:        Simple terminal file viewer

BuildRequires: make
BuildRequires: libncurses-devel

%description
Simple terminal file viewer.
Used for LecturesCMC/LinuxApplicationDevelopment2026/03_Packaging homework.

%prep
%setup -c

%build
make NAME=%name

%install
make install DESTDIR=%buildroot BINDIR=%_bindir

%files
%_bindir/*