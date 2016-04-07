
@echo off

REM 0.0.5
REM Cedric.bilat@he-arc.ch


REM -----------------------
REM - 	    Main	          -
REM -----------------------

@call shRuntime.cmd

pushd ..\linux

bash ../linux/symlink_workspace.sh

echo.
popd

REM -----------------------
REM - 	    END	          -
REM -----------------------




