Name:           most-likely-to-count
Version:        0.0.1
Release:        alt1
Summary:        Solves number puzzles
License:        MIT
Group:          Other
Url:            https://www.ioccc.org/2025/kurdyukov/index.html
Packager:       Maksim Kunts <private@mail.com>

Source:         %name-%version.tar.gz
BuildRequires:  gcc
BuildRequires:  make

%description

The program finds the shortest mathematical expression that uses numbers from the first list 
and +-*/ operators along with parentheses to represent numbers in the second list. 
Lists are separated by a zero.

Notes:
* Numbers are limited in the interval [1, 2^15).
* The shortest in terms of string length (spaces are counted).
* This may not be the shortest possible for some numbers due to the limited search range.

%prep
%setup

%build
cd kurdyukov
make all

%install
cd kurdyukov
mkdir -p %buildroot%_bindir
install -Dpm 0755 prog %buildroot%_bindir/%name
mkdir -p %buildroot%_docdir/%name
install -Dpm 0644 README.md %buildroot%_docdir/%name/README.md

%files
%_bindir/%name
%doc %_docdir/%name/README.md

%changelog
* Sat Oct 11 2025 Maksim Kunts <private@mail.com> 0.0.1-alt1
- Initial build