:: .\bootstrap.bat
:: .\b2 --build-dir=C:\ --build-type=complete --exec-prefix=C:\boost\ --libdir=C:\boost\ --includedir=C:\boost\ --stagedir=C:\boost\
:: 
:: mkdir C:\boost\include\boost
:: xcopy /E /Y .\boost C:\boost\include\boost

:: I cannot figure out why the building doesn't on windows!!!
:: For now, we will make exactly as it is done on EFVLib,
:: we will use the ../external_content/ folder to link.
:: For compatibility, we eill use it on linux also.
:: It is bad, but I can't find another way...

:: Make a directory exacty 'above' the ParticleSimulator folder.
:: It must looks like:
:: Folder_that_contains_the_Particle_simulatos_folder
::		external_content/
::			boost-1.55/
::				windows/
::				linux/
::		ParticleSimulator/