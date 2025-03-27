@echo off
powershell -ExecutionPolicy Bypass -File "%~dp0\image_processor.ps1" %1
