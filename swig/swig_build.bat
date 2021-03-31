mkdir build
swig -c++ -python -I../mahster -outdir build pymj_core.i
python setup.py build_ext
del pymj_core_wrap.cxx
pause
