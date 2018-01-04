DIST_SUBDIRS = secp256k1

AM_LDFLAGS = $(PTHREAD_CFLAGS) $(LIBTOOL_LDFLAGS) $(HARDENED_LDFLAGS)
AM_CXXFLAGS = $(HARDENED_CXXFLAGS)
AM_CPPFLAGS = $(HARDENED_CPPFLAGS)

if EMBEDDED_LEVELDB
LEVELDB_CPPFLAGS += -I$(srcdir)/leveldb/include
LEVELDB_CPPFLAGS += -I$(srcdir)/leveldb/helpers/memenv
LIBLEVELDB += $(builddir)/leveldb/libleveldb.a
LIBMEMENV  += $(builddir)/leveldb/libmemenv.a

# NOTE: This dependency is not strictly necessary, but without it make may try to build both in parallel, which breaks the LevelDB build system in a race
$(LIBLEVELDB): $(LIBMEMENV)

$(LIBLEVELDB) $(LIBMEMENV):
	@echo "Building LevelDB ..." && $(MAKE) -C $(@D) $(@F) CXX="$(CXX)" \
	  CC="$(CC)" PLATFORM=$(TARGET_OS) AR="$(AR)" $(LEVELDB_TARGET_FLAGS) \
          OPT="$(AM_CXXFLAGS) $(PIE_FLAGS) $(CXXFLAGS) $(AM_CPPFLAGS) $(CPPFLAGS) -D__STDC_LIMIT_MACROS"
endif

CUCKOOCOIN_CONFIG_INCLUDES=-I$(builddir)/config
CUCKOOCOIN_INCLUDES=-I$(builddir) -I$(builddir)/obj $(BOOST_CPPFLAGS) $(LEVELDB_CPPFLAGS) $(CRYPTO_CFLAGS) $(SSL_CFLAGS)

CUCKOOCOIN_INCLUDES += -I$(srcdir)/secp256k1/include

LIBCUCKOOCOIN_SERVER=libcuckoocoin_server.a
LIBCUCKOOCOIN_WALLET=libcuckoocoin_wallet.a
LIBCUCKOOCOIN_COMMON=libcuckoocoin_common.a
LIBCUCKOOCOIN_CLI=libcuckoocoin_cli.a
LIBCUCKOOCOIN_UTIL=libcuckoocoin_util.a
LIBCUCKOOCOIN_CRYPTO=crypto/libcuckoocoin_crypto.a
LIBCUCKOOCOIN_UNIVALUE=univalue/libcuckoocoin_univalue.a
LIBCUCKOOCOINQT=qt/libcuckoocoinqt.a
LIBSECP256K1=secp256k1/libsecp256k1.la

$(LIBSECP256K1): $(wildcard secp256k1/src/*) $(wildcard secp256k1/include/*)
	$(AM_V_at)$(MAKE) $(AM_MAKEFLAGS) -C $(@D) $(@F)

# Make is not made aware of per-object dependencies to avoid limiting building parallelization
# But to build the less dependent modules first, we manually select their order here:
EXTRA_LIBRARIES = \
  crypto/libcuckoocoin_crypto.a \
  libcuckoocoin_util.a \
  libcuckoocoin_common.a \
  univalue/libcuckoocoin_univalue.a \
  libcuckoocoin_server.a \
  libcuckoocoin_cli.a
if ENABLE_WALLET
CUCKOOCOIN_INCLUDES += $(BDB_CPPFLAGS)
EXTRA_LIBRARIES += libcuckoocoin_wallet.a
endif

if BUILD_CUCKOOCOIN_LIBS
lib_LTLIBRARIES = libcuckoocoinconsensus.la
LIBCUCKOOCOIN_CONSENSUS=libcuckoocoinconsensus.la
else
LIBCUCKOOCOIN_CONSENSUS=
endif

bin_PROGRAMS =
TESTS =

if BUILD_CUCKOOCOIND
  bin_PROGRAMS += cuckoocoind
endif

if BUILD_CUCKOOCOIN_UTILS
  bin_PROGRAMS += cuckoocoin-cli cuckoocoin-tx
endif

.PHONY: FORCE
# cuckoocoin core #
CUCKOOCOIN_CORE_H = \
  addrman.h \
  alert.h \
  amount.h \
  arith_uint256.h \
  base58.h \
  bloom.h \
  chain.h \
  chainparams.h \
  chainparamsbase.h \
  chainparamsseeds.h \
  checkpoints.h \
  checkqueue.h \
  clientversion.h \
  coincontrol.h \
  coins.h \
  compat.h \
  compat/byteswap.h \
  compat/endian.h \
  compat/sanity.h \
  compressor.h \
  consensus/consensus.h \
  consensus/params.h \
  consensus/validation.h \
  core_io.h \
  eccryptoverify.h \
  ecwrapper.h \
  hash.h \
  init.h \
  key.h \
  keystore.h \
  leveldbwrapper.h \
  limitedmap.h \
  main.h \
  memusage.h \
  merkleblock.h \
  miner.h \
  mruset.h \
  net.h \
  netbase.h \
  noui.h \
  policy/fees.h \
  pow.h \
  primitives/block.h \
  primitives/transaction.h \
  protocol.h \
  pubkey.h \
  random.h \
  reverselock.h \
  rpcclient.h \
  rpcprotocol.h \
  rpcserver.h \
  scheduler.h \
  script/interpreter.h \
  script/script.h \
  script/script_error.h \
  script/sigcache.h \
  script/sign.h \
  script/standard.h \
  serialize.h \
  streams.h \
  support/allocators/secure.h \
  support/allocators/zeroafterfree.h \
  support/cleanse.h \
  support/pagelocker.h \
  sync.h \
  threadsafety.h \
  timedata.h \
  tinyformat.h \
  txdb.h \
  txmempool.h \
  ui_interface.h \
  uint256.h \
  undo.h \
  util.h \
  utilmoneystr.h \
  utilstrencodings.h \
  utiltime.h \
  validationinterface.h \
  version.h \
  wallet/crypter.h \
  wallet/db.h \
  wallet/wallet.h \
  wallet/wallet_ismine.h \
  wallet/walletdb.h

JSON_H = \
  json/json_spirit.h \
  json/json_spirit_error_position.h \
  json/json_spirit_reader.h \
  json/json_spirit_reader_template.h \
  json/json_spirit_stream_reader.h \
  json/json_spirit_utils.h \
  json/json_spirit_value.h \
  json/json_spirit_writer.h \
  json/json_spirit_writer_template.h

obj/build.h: FORCE
	@$(MKDIR_P) $(builddir)/obj
	@$(top_srcdir)/share/genbuild.sh $(abs_top_builddir)/src/obj/build.h \
	  $(abs_top_srcdir)
libcuckoocoin_util_a-clientversion.$(OBJEXT): obj/build.h

# server: shared between cuckoocoind and cuckoocoin-qt
libcuckoocoin_server_a_CPPFLAGS = $(AM_CPPFLAGS) $(CUCKOOCOIN_INCLUDES) $(MINIUPNPC_CPPFLAGS)
libcuckoocoin_server_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libcuckoocoin_server_a_SOURCES = \
  addrman.cpp \
  alert.cpp \
  bloom.cpp \
  chain.cpp \
  checkpoints.cpp \
  init.cpp \
  leveldbwrapper.cpp \
  main.cpp \
  merkleblock.cpp \
  miner.cpp \
  net.cpp \
  noui.cpp \
  policy/fees.cpp \
  pow.cpp \
  rest.cpp \
  rpcblockchain.cpp \
  rpcmining.cpp \
  rpcmisc.cpp \
  rpcnet.cpp \
  rpcrawtransaction.cpp \
  rpcserver.cpp \
  script/sigcache.cpp \
  timedata.cpp \
  txdb.cpp \
  txmempool.cpp \
  validationinterface.cpp \
  $(JSON_H) \
  $(CUCKOOCOIN_CORE_H)

# wallet: shared between cuckoocoind and cuckoocoin-qt, but only linked
# when wallet enabled
libcuckoocoin_wallet_a_CPPFLAGS = $(AM_CPPFLAGS) $(CUCKOOCOIN_INCLUDES)
libcuckoocoin_wallet_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libcuckoocoin_wallet_a_SOURCES = \
  wallet/crypter.cpp \
  wallet/db.cpp \
  wallet/rpcdump.cpp \
  wallet/rpcwallet.cpp \
  wallet/wallet.cpp \
  wallet/wallet_ismine.cpp \
  wallet/walletdb.cpp \
  $(CUCKOOCOIN_CORE_H)

# crypto primitives library
crypto_libcuckoocoin_crypto_a_CPPFLAGS = $(AM_CPPFLAGS) $(CUCKOOCOIN_CONFIG_INCLUDES)
crypto_libcuckoocoin_crypto_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
crypto_libcuckoocoin_crypto_a_SOURCES = \
  crypto/common.h \
  crypto/hmac_sha256.cpp \
  crypto/hmac_sha256.h \
  crypto/hmac_sha512.cpp \
  crypto/hmac_sha512.h \
  crypto/ripemd160.cpp \
  crypto/ripemd160.h \
  crypto/sha1.cpp \
  crypto/sha1.h \
  crypto/sha256.cpp \
  crypto/sha256.h \
  crypto/sha512.cpp \
  crypto/sha512.h

# univalue JSON library
univalue_libcuckoocoin_univalue_a_CPPFLAGS = $(AM_CPPFLAGS)
univalue_libcuckoocoin_univalue_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
univalue_libcuckoocoin_univalue_a_SOURCES = \
  univalue/univalue.cpp \
  univalue/univalue.h \
  univalue/univalue_escapes.h \
  univalue/univalue_read.cpp \
  univalue/univalue_write.cpp

# common: shared between cuckoocoind, and cuckoocoin-qt and non-server tools
libcuckoocoin_common_a_CPPFLAGS = $(AM_CPPFLAGS) $(CUCKOOCOIN_INCLUDES)
libcuckoocoin_common_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libcuckoocoin_common_a_SOURCES = \
  amount.cpp \
  arith_uint256.cpp \
  base58.cpp \
  chainparams.cpp \
  coins.cpp \
  compressor.cpp \
  core_read.cpp \
  core_write.cpp \
  eccryptoverify.cpp \
  ecwrapper.cpp \
  hash.cpp \
  key.cpp \
  keystore.cpp \
  netbase.cpp \
  primitives/block.cpp \
  primitives/transaction.cpp \
  protocol.cpp \
  pubkey.cpp \
  scheduler.cpp \
  script/interpreter.cpp \
  script/script.cpp \
  script/script_error.cpp \
  script/sign.cpp \
  script/standard.cpp \
  $(CUCKOOCOIN_CORE_H)

# util: shared between all executables.
# This library *must* be included to make sure that the glibc
# backward-compatibility objects and their sanity checks are linked.
libcuckoocoin_util_a_CPPFLAGS = $(AM_CPPFLAGS) $(CUCKOOCOIN_INCLUDES)
libcuckoocoin_util_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libcuckoocoin_util_a_SOURCES = \
  support/pagelocker.cpp \
  chainparamsbase.cpp \
  clientversion.cpp \
  compat/glibc_sanity.cpp \
  compat/glibcxx_sanity.cpp \
  compat/strnlen.cpp \
  random.cpp \
  rpcprotocol.cpp \
  support/cleanse.cpp \
  sync.cpp \
  uint256.cpp \
  util.cpp \
  utilmoneystr.cpp \
  utilstrencodings.cpp \
  utiltime.cpp \
  $(CUCKOOCOIN_CORE_H)

if GLIBC_BACK_COMPAT
libcuckoocoin_util_a_SOURCES += compat/glibc_compat.cpp
endif

# cli: shared between cuckoocoin-cli and cuckoocoin-qt
libcuckoocoin_cli_a_CPPFLAGS = $(AM_CPPFLAGS) $(CUCKOOCOIN_INCLUDES)
libcuckoocoin_cli_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libcuckoocoin_cli_a_SOURCES = \
  rpcclient.cpp \
  $(CUCKOOCOIN_CORE_H)

nodist_libcuckoocoin_util_a_SOURCES = $(srcdir)/obj/build.h
#

# cuckoocoind binary #
cuckoocoind_SOURCES = cuckoocoind.cpp
cuckoocoind_CPPFLAGS = $(AM_CPPFLAGS) $(CUCKOOCOIN_INCLUDES)
cuckoocoind_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
cuckoocoind_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)

if TARGET_WINDOWS
cuckoocoind_SOURCES += cuckoocoind-res.rc
endif

cuckoocoind_LDADD = \
  $(LIBCUCKOOCOIN_SERVER) \
  $(LIBCUCKOOCOIN_COMMON) \
  $(LIBCUCKOOCOIN_UNIVALUE) \
  $(LIBCUCKOOCOIN_UTIL) \
  $(LIBCUCKOOCOIN_CRYPTO) \
  $(LIBLEVELDB) \
  $(LIBMEMENV) \
  $(LIBSECP256K1)

if ENABLE_WALLET
cuckoocoind_LDADD += libcuckoocoin_wallet.a
endif

cuckoocoind_LDADD += $(BOOST_LIBS) $(BDB_LIBS) $(SSL_LIBS) $(CRYPTO_LIBS) $(MINIUPNPC_LIBS)
#

# cuckoocoin-cli binary #
cuckoocoin_cli_SOURCES = cuckoocoin-cli.cpp
cuckoocoin_cli_CPPFLAGS = $(AM_CPPFLAGS) $(CUCKOOCOIN_INCLUDES)
cuckoocoin_cli_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
cuckoocoin_cli_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)

if TARGET_WINDOWS
cuckoocoin_cli_SOURCES += cuckoocoin-cli-res.rc
endif

cuckoocoin_cli_LDADD = \
  $(LIBCUCKOOCOIN_CLI) \
  $(LIBCUCKOOCOIN_UTIL)

cuckoocoin_cli_LDADD += $(BOOST_LIBS) $(SSL_LIBS) $(CRYPTO_LIBS)
#

# cuckoocoin-tx binary #
cuckoocoin_tx_SOURCES = cuckoocoin-tx.cpp
cuckoocoin_tx_CPPFLAGS = $(AM_CPPFLAGS) $(CUCKOOCOIN_INCLUDES)
cuckoocoin_tx_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
cuckoocoin_tx_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)

if TARGET_WINDOWS
cuckoocoin_tx_SOURCES += cuckoocoin-tx-res.rc
endif

cuckoocoin_tx_LDADD = \
  $(LIBCUCKOOCOIN_UNIVALUE) \
  $(LIBCUCKOOCOIN_COMMON) \
  $(LIBCUCKOOCOIN_UTIL) \
  $(LIBCUCKOOCOIN_CRYPTO) \
  $(LIBSECP256K1)

cuckoocoin_tx_LDADD += $(BOOST_LIBS) $(CRYPTO_LIBS)
#

# cuckoocoinconsensus library #
if BUILD_CUCKOOCOIN_LIBS
include_HEADERS = script/cuckoocoinconsensus.h
libcuckoocoinconsensus_la_SOURCES = \
  crypto/hmac_sha512.cpp \
  crypto/ripemd160.cpp \
  crypto/sha1.cpp \
  crypto/sha256.cpp \
  crypto/sha512.cpp \
  eccryptoverify.cpp \
  ecwrapper.cpp \
  hash.cpp \
  primitives/transaction.cpp \
  pubkey.cpp \
  script/cuckoocoinconsensus.cpp \
  script/interpreter.cpp \
  script/script.cpp \
  uint256.cpp \
  utilstrencodings.cpp

if GLIBC_BACK_COMPAT
  libcuckoocoinconsensus_la_SOURCES += compat/glibc_compat.cpp
endif

libcuckoocoinconsensus_la_LDFLAGS = $(AM_LDFLAGS) -no-undefined $(RELDFLAGS)
libcuckoocoinconsensus_la_LIBADD = $(CRYPTO_LIBS)
libcuckoocoinconsensus_la_CPPFLAGS = $(AM_CPPFLAGS) $(CRYPTO_CFLAGS) -I$(builddir)/obj -DBUILD_CUCKOOCOIN_INTERNAL
libcuckoocoinconsensus_la_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)

endif
#

CLEANFILES = leveldb/libleveldb.a leveldb/libmemenv.a *.gcda *.gcno

DISTCLEANFILES = obj/build.h

EXTRA_DIST = leveldb

clean-local:
	-$(MAKE) -C leveldb clean
	-$(MAKE) -C secp256k1 clean
	rm -f leveldb/*/*.gcno leveldb/helpers/memenv/*.gcno
	-rm -f config.h

.rc.o:
	@test -f $(WINDRES)
	$(AM_V_GEN) $(WINDRES) -DWINDRES_PREPROC -i $< -o $@

%.pb.cc %.pb.h: %.proto
	@test -f $(PROTOC)
	$(AM_V_GEN) $(PROTOC) --cpp_out=$(@D) --proto_path=$(abspath $(<D) $<)

if ENABLE_TESTS
include Makefile.test.include
endif

if ENABLE_QT
include Makefile.qt.include
endif

if ENABLE_QT_TESTS
include Makefile.qttest.include
endif
