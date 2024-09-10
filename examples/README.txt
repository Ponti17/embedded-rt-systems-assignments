Properties:

C/C++ -> General -> Addition Include Directories
$(SYSTEMC_HOME)\src;%(AdditionalIncludeDirectories)

C/C++ -> Language -> Enable Run-Time Type Information
Yes (/GR)

C/C++ -> Precompiled Headers -> Precompiled Headers
Not Using Precompiled Headers

C/C++ -> All Options -> Additional Options
/vmg %(AdditionalOptions)


Linker -> General > Additional Library Directories
$(SYSTEMC_HOME)\msvc16\SystemC\$(IntDir);%(AdditionalLibraryDirectories)


Linker -> Input -> Additional Dependencies
systemc.lib;%(AdditionalDependencies)

