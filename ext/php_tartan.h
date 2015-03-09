
/* This file was generated automatically by Zephir do not modify it! */

#ifndef PHP_TARTAN_H
#define PHP_TARTAN_H 1

#ifdef PHP_WIN32
#define ZEPHIR_RELEASE 1
#endif

#include "kernel/globals.h"

#define PHP_TARTAN_NAME        "tartan"
#define PHP_TARTAN_VERSION     "0.0.1"
#define PHP_TARTAN_EXTNAME     "tartan"
#define PHP_TARTAN_AUTHOR      "Aboozar Ghaffari"
#define PHP_TARTAN_ZEPVERSION  "0.6.0a"
#define PHP_TARTAN_DESCRIPTION "extended phalcon php framework"



ZEND_BEGIN_MODULE_GLOBALS(tartan)

	int initialized;

	/* Memory */
	zephir_memory_entry *start_memory; /**< The first preallocated frame */
	zephir_memory_entry *end_memory; /**< The last preallocate frame */
	zephir_memory_entry *active_memory; /**< The current memory frame */

	/* Virtual Symbol Tables */
	zephir_symbol_table *active_symbol_table;

	/** Function cache */
	HashTable *fcache;

	/* Cache enabled */
	unsigned int cache_enabled;

	/* Max recursion control */
	unsigned int recursive_lock;

	/* Global constants */
	zval *global_true;
	zval *global_false;
	zval *global_null;
	
ZEND_END_MODULE_GLOBALS(tartan)

#ifdef ZTS
#include "TSRM.h"
#endif

ZEND_EXTERN_MODULE_GLOBALS(tartan)

#ifdef ZTS
	#define ZEPHIR_GLOBAL(v) TSRMG(tartan_globals_id, zend_tartan_globals *, v)
#else
	#define ZEPHIR_GLOBAL(v) (tartan_globals.v)
#endif

#ifdef ZTS
	#define ZEPHIR_VGLOBAL ((zend_tartan_globals *) (*((void ***) tsrm_ls))[TSRM_UNSHUFFLE_RSRC_ID(tartan_globals_id)])
#else
	#define ZEPHIR_VGLOBAL &(tartan_globals)
#endif

#define ZEPHIR_API ZEND_API

#define zephir_globals_def tartan_globals
#define zend_zephir_globals_def zend_tartan_globals

extern zend_module_entry tartan_module_entry;
#define phpext_tartan_ptr &tartan_module_entry

#endif
