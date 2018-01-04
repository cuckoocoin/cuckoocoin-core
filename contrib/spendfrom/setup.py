from distutils.core import setup
setup(name='cucspendfrom',
      version='1.0',
      description='Command-line utility for cuckoocoin "coin control"',
      author='Gavin Andresen',
      author_email='gavin@cuckoocoinfoundation.org',
      requires=['jsonrpc'],
      scripts=['spendfrom.py'],
      )
