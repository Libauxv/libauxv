Name: auxv
Version: 1.0.0
Release: 0
Summary: The Auxilary-Vector Library

License: New BSD License
URL: https://github.com/Libauxv/libauxv
Source0: %{name}-%{version}.tar.gz

%description
Libauxv provides access to the 5th process variable, the auxiliary vector. It
uses the most reliable method, i.e.: querying the aux vector through
/proc/self/auxv. When /proc/self/auxv is not supported by the kernel, libauxv
still works, using a fallback method.
Libraries should use libaux to access auxv information, because they have no
access to 'main' and trying to find auxv after env has no guarantees, since the
environment may have been mangled.

# Uncomment the following line to generate a debuginfo package on SUSE systems.
# NOTE: On Fedora and RHEL systems, the following line cannot be uncommented,
#       because such systems define and generate debuginfo packages by default.
#%%debug_package


%prep
%setup -q


%build
%configure --docdir=%{_docdir}/%{name}
make %{?_smp_mflags}


%check
make check


%install
rm -rf $RPM_BUILD_ROOT
%make_install

%files
%defattr(-,root,root)
%{_bindir}/lsauxv
%{_docdir}/%{name}/COPYING.txt
%{_docdir}/%{name}/GFDLv1.3.txt
%{_docdir}/%{name}/README
%{_includedir}/auxv/auxv.h
%{_includedir}/auxv/hwcap.h
%{_libdir}/libauxv.a
%{_libdir}/libauxv.la
%{_libdir}/libauxv.so*
%{_mandir}/man1/lsauxv.1.gz
%{_mandir}/man3/auxv.3.gz
%{_mandir}/man3/libauxv.3.gz


%changelog
* Thu May 14 2015 Gabriel F T Gomes <gftg@linux.vnet.ibm.com> - 1.0.0-0
- Initial version of the package
