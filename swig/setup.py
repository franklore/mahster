from distutils.core import setup, Extension

module = Extension('_pymj_core', sources=['pymj_core_wrap.cxx'])

setup(name = 'pymj_core',
      version = '0.1',
      author = 'Franklore',
      description = """pymj core""",
      ext_modules = [module],
      py_modules = ['pymj_core'],
      )