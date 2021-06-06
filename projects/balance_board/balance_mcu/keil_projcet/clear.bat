del *.bak /s
del *.ddk /s
del *.edk /s
del *.lst /s
del *.lnp /s
del *.mpf /s
del *.mpj /s
del *.obj /s
del *.omf /s
del *.opt /s
del Release/*.sct /s  
del *.plg /s
del *.rpt /s
del *.tmp /s
del *.__i /s
del *.crf /s
del *.o /s
del *.d /s
del *.axf /s
del *.tra /s
del *.dep /s           
del JLinkLog.txt /s
del *.iex /s
del *.htm /s
del *.map /s
del *.dbgconf /s
del *.uvguix.* /s
del *.uvoptx /s
del *.0000 /s
del *.scvd /s
del *.ini /s
del *.hex /s
del RTE_Components.h /s

rd /q /s DebugConfig
rd /q /s Listings
rd /q /s Objects
rd /q /s RTE\_STM32F103xx
rd /q /s RTE\_STM32F10x

exit