/*
 * Copyright 1998-2003 The OpenLDAP Foundation, All Rights Reserved.
 * COPYING RESTRICTIONS APPLY, see COPYRIGHT file
 */
/*
 * (C) Copyright IBM Corp. 1997,2002
 * Redistribution and use in source and binary forms are permitted
 * provided that this notice is preserved and that due credit is
 * given to IBM Corporation. This software is provided ``as is''
 * without express or implied warranty.
 */

#ifndef _SLAPI_PLUGIN_H
#define _SLAPI_PLUGIN_H

#include <lber.h>
#include <ldap.h>

typedef struct slapi_pblock	Slapi_PBlock;
typedef struct slapi_entry	Slapi_Entry;
typedef struct slapi_attr	Slapi_Attr;
typedef struct berval		Slapi_Value;
typedef struct BerVarray	Slapi_ValueSet;
typedef struct slapi_filter	Slapi_Filter;

/* pblock routines */
int slapi_pblock_get( Slapi_PBlock *pb, int arg, void *value );
int slapi_pblock_set( Slapi_PBlock *pb, int arg, void *value );
Slapi_PBlock *slapi_pblock_new();
void slapi_pblock_destroy( Slapi_PBlock* );

/* entry/attr/dn routines */
Slapi_Entry *slapi_str2entry( char *s, int flags );
char *slapi_entry2str( Slapi_Entry *e, int *len );
char *slapi_entry_get_dn( Slapi_Entry *e );
int slapi_x_entry_get_id( Slapi_Entry *e );
void slapi_entry_set_dn( Slapi_Entry *e, char *dn );
Slapi_Entry *slapi_entry_dup( Slapi_Entry *e );
int slapi_entry_attr_delete( Slapi_Entry *e, char *type );
Slapi_Entry *slapi_entry_alloc();
void slapi_entry_free( Slapi_Entry *e );
int slapi_entry_attr_merge( Slapi_Entry *e, char *type, struct berval **vals );
int slapi_entry_attr_find( Slapi_Entry *e, char *type, Slapi_Attr **attr );
char *slapi_entry_attr_get_charptr( const Slapi_Entry *e, const char *type );
int slapi_entry_attr_get_int( const Slapi_Entry *e, const char *type );
int slapi_entry_attr_get_long( const Slapi_Entry *e, const char *type );
int slapi_entry_attr_get_uint( const Slapi_Entry *e, const char *type );
int slapi_entry_attr_get_ulong( const Slapi_Entry *e, const char *type );
int slapi_attr_get_values( Slapi_Attr *attr, struct berval ***vals );
char *slapi_dn_normalize( char *dn );
char *slapi_dn_normalize_case( char *dn );
int slapi_dn_issuffix( char *dn, char *suffix );
char *slapi_dn_ignore_case( char *dn );

/* DS 5.x SLAPI */
int slapi_access_allowed( Slapi_PBlock *pb, Slapi_Entry *e, char *attr, struct berval *val, int access );
int slapi_acl_check_mods( Slapi_PBlock *pb, Slapi_Entry *e, LDAPMod **mods, char **errbuf );
Slapi_Attr *slapi_attr_new( void );
Slapi_Attr *slapi_attr_init( Slapi_Attr *a, const char *type );
void slapi_attr_free( Slapi_Attr **a );
Slapi_Attr *slapi_attr_dup( const Slapi_Attr *attr );
int slapi_attr_add_value( Slapi_Attr *a, const Slapi_Value *v );
int slapi_attr_type2plugin( const char *type, void **pi );
int slapi_attr_get_type( const Slapi_Attr *attr, char **type );
int slapi_attr_get_oid_copy( const Slapi_Attr *attr, char **oidp );
int slapi_attr_get_flags( const Slapi_Attr *attr, unsigned long *flags );
int slapi_attr_flag_is_set( const Slapi_Attr *attr, unsigned long flag );
int slapi_attr_value_cmp( const Slapi_Attr *attr, const struct berval *v1, const struct berval *v2 );
int slapi_attr_value_find( const Slapi_Attr *a, struct berval *v );
#define SLAPI_TYPE_CMP_EXACT	0
#define SLAPI_TYPE_CMP_BASE	1
#define SLAPI_TYPE_CMP_SUBTYPE	2
int slapi_attr_type_cmp( const char *t1, const char *t2, int opt );
int slapi_attr_types_equivalent( const char *t1, const char *t2 );
int slapi_attr_first_value( Slapi_Attr *a, Slapi_Value **v );
int slapi_attr_next_value( Slapi_Attr *a, int hint, Slapi_Value **v );
int slapi_attr_get_numvalues( const Slapi_Attr *a, int *numValues );
int slapi_attr_get_valueset( const Slapi_Attr *a, Slapi_ValueSet **vs );
int slapi_attr_get_bervals_copy( Slapi_Attr *a, struct berval ***vals );
int slapi_entry_attr_hasvalue( Slapi_Entry *e, const char *type, const char *value );
int slapi_entry_attr_merge_sv( Slapi_Entry *e, const char *type, Slapi_Value **vals );
char *slapi_attr_syntax_normalize( const char *s );

Slapi_Value *slapi_value_new( void );
Slapi_Value *slapi_value_new_berval(const struct berval *bval);
Slapi_Value *slapi_value_new_value(const Slapi_Value *v);
Slapi_Value *slapi_value_new_string(const char *s);
Slapi_Value *slapi_value_init(Slapi_Value *v);
Slapi_Value *slapi_value_init_berval(Slapi_Value *v, struct berval *bval);
Slapi_Value *slapi_value_init_string(Slapi_Value *v,const char *s);
Slapi_Value *slapi_value_dup(const Slapi_Value *v);
void slapi_value_free(Slapi_Value **value);
const struct berval *slapi_value_get_berval( const Slapi_Value *value );
Slapi_Value *slapi_value_set_berval( Slapi_Value *value, const struct berval *bval );
Slapi_Value *slapi_value_set_value( Slapi_Value *value, const Slapi_Value *vfrom);
Slapi_Value *slapi_value_set( Slapi_Value *value, void *val, unsigned long len);
int slapi_value_set_string(Slapi_Value *value, const char *strVal);
int slapi_value_set_int(Slapi_Value *value, int intVal);
const char*slapi_value_get_string(const Slapi_Value *value);
int slapi_value_get_int(const Slapi_Value *value); 
unsigned int slapi_value_get_uint(const Slapi_Value *value); 
long slapi_value_get_long(const Slapi_Value *value); 
unsigned long slapi_value_get_ulong(const Slapi_Value *value); 
size_t slapi_value_get_length(const Slapi_Value *value);
int slapi_value_compare(const Slapi_Attr *a,const Slapi_Value *v1,const Slapi_Value *v2);

Slapi_ValueSet *slapi_valueset_new( void );
void slapi_valueset_free(Slapi_ValueSet *vs);
void slapi_valueset_init(Slapi_ValueSet *vs);
void slapi_valueset_done(Slapi_ValueSet *vs);
void slapi_valueset_add_value(Slapi_ValueSet *vs, const Slapi_Value *addval);
int slapi_valueset_first_value( Slapi_ValueSet *vs, Slapi_Value **v );
int slapi_valueset_next_value( Slapi_ValueSet *vs, int index, Slapi_Value **v);
int slapi_valueset_count( const Slapi_ValueSet *vs);
void slapi_valueset_set_valueset(Slapi_ValueSet *vs1, const Slapi_ValueSet *vs2);

char *slapi_ch_malloc( unsigned long size );
void slapi_ch_free( void **ptr );
void slapi_ch_free_string( char **ptr );
char *slapi_ch_calloc( unsigned long nelem, unsigned long size );
char *slapi_ch_realloc( char *block, unsigned long size );
char *slapi_ch_strdup( char *s );
void slapi_ch_array_free( char **arrayp );
struct berval *slapi_ch_bvdup(const struct berval *v);
struct berval **slapi_ch_bvecdup(const struct berval **v);

/* LDAP V3 routines */
int slapi_control_present( LDAPControl **controls, char *oid,
	struct berval **val, int *iscritical);
void slapi_register_supported_control(char *controloid,
	unsigned long controlops);
#define SLAPI_OPERATION_BIND            0x00000001L
#define SLAPI_OPERATION_UNBIND          0x00000002L
#define SLAPI_OPERATION_SEARCH          0x00000004L
#define SLAPI_OPERATION_MODIFY          0x00000008L
#define SLAPI_OPERATION_ADD             0x00000010L
#define SLAPI_OPERATION_DELETE          0x00000020L
#define SLAPI_OPERATION_MODDN           0x00000040L
#define SLAPI_OPERATION_MODRDN          SLAPI_OPERATION_MODDN
#define SLAPI_OPERATION_COMPARE         0x00000080L
#define SLAPI_OPERATION_ABANDON         0x00000100L
#define SLAPI_OPERATION_EXTENDED        0x00000200L
#define SLAPI_OPERATION_ANY             0xFFFFFFFFL
#define SLAPI_OPERATION_NONE            0x00000000L
int slapi_get_supported_controls(char ***ctrloidsp, unsigned long **ctrlopsp);
void slapi_register_supported_saslmechanism(char *mechanism);
char **slapi_get_supported_saslmechanisms();
char **slapi_get_supported_extended_ops(void);


/* send ldap result back */
void slapi_send_ldap_result( Slapi_PBlock *pb, int err, char *matched,
	char *text, int nentries, struct berval **urls );
int slapi_send_ldap_search_entry( Slapi_PBlock *pb, Slapi_Entry *e,
	LDAPControl **ectrls, char **attrs, int attrsonly );

/* filter routines */
Slapi_Filter *slapi_str2filter( char *str );
void slapi_filter_free( Slapi_Filter *f, int recurse );
int slapi_filter_get_choice( Slapi_Filter *f);
int slapi_filter_get_ava( Slapi_Filter *f, char **type, struct berval **bval );
Slapi_Filter *slapi_filter_list_first( Slapi_Filter *f );
Slapi_Filter *slapi_filter_list_next( Slapi_Filter *f, Slapi_Filter *fprev );

/* internal add/delete/search/modify routines */
Slapi_PBlock *slapi_search_internal( char *base, int scope, char *filter, 
	LDAPControl **controls, char **attrs, int attrsonly );
Slapi_PBlock *slapi_modify_internal( char *dn, LDAPMod **mods,
        LDAPControl **controls, int log_change);
Slapi_PBlock *slapi_add_entry_internal( Slapi_Entry * e,
	LDAPControl **controls, int log_change );
Slapi_PBlock *slapi_add_internal( char * dn, LDAPMod **attrs,
	LDAPControl **controls, int log_changes );
Slapi_PBlock *slapi_add_entry_internal( Slapi_Entry * e,
	LDAPControl **controls, int log_change );
Slapi_PBlock *slapi_delete_internal( char * dn,  LDAPControl **controls,
	int log_change );
Slapi_PBlock *slapi_modrdn_internal( char * olddn, char * newrdn,
	char *newParent, int deloldrdn, LDAPControl **controls,
	int log_change);
void slapi_free_search_results_internal(Slapi_PBlock *pb);

/* connection related routines */
int slapi_is_connection_ssl(Slapi_PBlock *pPB, int *isSSL);
int slapi_get_client_port(Slapi_PBlock *pPB, int *fromPort);

/* computed attributes */
struct _computed_attr_context;
typedef struct _computed_attr_context computed_attr_context;
typedef int (*slapi_compute_output_t)(computed_attr_context *c, Slapi_Attr *a, Slapi_Entry *e);
typedef int (*slapi_compute_callback_t)(computed_attr_context *c, char *type, Slapi_Entry *e, slapi_compute_output_t outputfn);
typedef int (*slapi_search_rewrite_callback_t)(Slapi_PBlock *pb);
int slapi_compute_add_evaluator(slapi_compute_callback_t function);
int slapi_compute_add_search_rewriter(slapi_search_rewrite_callback_t function);
int compute_rewrite_search_filter(Slapi_PBlock *pb);
int compute_evaluator(computed_attr_context *c, char *type, Slapi_Entry *e, slapi_compute_output_t outputfn);
int slapi_x_compute_get_pblock(computed_attr_context *c, Slapi_PBlock **pb);

/* parameters currently supported */

/*
 * Attribute flags returned by slapi_attr_get_flags()
 */
#define SLAPI_ATTR_FLAG_SINGLE		0x0001
#define SLAPI_ATTR_FLAG_OPATTR		0x0002
#define SLAPI_ATTR_FLAG_READONLY	0x0004
#define SLAPI_ATTR_FLAG_STD_ATTR	SLAPI_ATTR_FLAG_READONLY
#define SLAPI_ATTR_FLAG_OBSOLETE	0x0040
#define SLAPI_ATTR_FLAG_COLLECTIVE	0x0080
#define SLAPI_ATTR_FLAG_NOUSERMOD	0x0100

/*
 * ACL levels
 */
#define SLAPI_ACL_COMPARE       0x01
#define SLAPI_ACL_SEARCH        0x02
#define SLAPI_ACL_READ          0x04
#define SLAPI_ACL_WRITE         0x08
#define SLAPI_ACL_DELETE        0x10    
#define SLAPI_ACL_ADD           0x20
#define SLAPI_ACL_SELF          0x40
#define SLAPI_ACL_PROXY         0x80
#define SLAPI_ACL_ALL           0x7f

/* plugin types supported */

#define SLAPI_PLUGIN_DATABASE           1
#define SLAPI_PLUGIN_EXTENDEDOP         2
#define SLAPI_PLUGIN_PREOPERATION       3
#define SLAPI_PLUGIN_POSTOPERATION      4
#define SLAPI_PLUGIN_AUDIT              7   

/* misc params */

#define SLAPI_BACKEND				130
#define SLAPI_CONNECTION			131
#define SLAPI_OPERATION				132
#define SLAPI_REQUESTOR_ISROOT			133
#define SLAPI_BE_MONITORDN			134
#define SLAPI_BE_TYPE           		135
#define SLAPI_BE_READONLY       		136
#define SLAPI_BE_LASTMOD       			137
#define SLAPI_CONN_ID        			139

/* operation params */
#define SLAPI_OPINITIATED_TIME			140
#define SLAPI_REQUESTOR_DN			141
#define SLAPI_REQUESTOR_ISUPDATEDN		142

/* connection  structure params*/
#define SLAPI_CONN_DN        			143
#define SLAPI_CONN_AUTHTYPE    			144

/*  Authentication types */
#define SLAPD_AUTH_NONE   "none"
#define SLAPD_AUTH_SIMPLE "simple"
#define SLAPD_AUTH_SSL    "SSL"
#define SLAPD_AUTH_SASL   "SASL " 

/* plugin configuration parmams */
#define SLAPI_PLUGIN				3
#define SLAPI_PLUGIN_PRIVATE			4
#define SLAPI_PLUGIN_TYPE			5
#define SLAPI_PLUGIN_ARGV			6
#define SLAPI_PLUGIN_ARGC			7
#define SLAPI_PLUGIN_VERSION			8
#define SLAPI_PLUGIN_OPRETURN			9
#define SLAPI_PLUGIN_OBJECT			10
#define SLAPI_PLUGIN_DESTROY_FN			11
#define SLAPI_PLUGIN_DESCRIPTION		12

/* internal opreations params */
#define SLAPI_PLUGIN_INTOP_RESULT		15
#define SLAPI_PLUGIN_INTOP_SEARCH_ENTRIES	16
#define SLAPI_PLUGIN_INTOP_SEARCH_REFERRALS	17

/* function pointer params for backends */
#define SLAPI_PLUGIN_DB_BIND_FN			200
#define SLAPI_PLUGIN_DB_UNBIND_FN		201
#define SLAPI_PLUGIN_DB_SEARCH_FN		202
#define SLAPI_PLUGIN_DB_COMPARE_FN		203
#define SLAPI_PLUGIN_DB_MODIFY_FN		204
#define SLAPI_PLUGIN_DB_MODRDN_FN		205
#define SLAPI_PLUGIN_DB_ADD_FN			206
#define SLAPI_PLUGIN_DB_DELETE_FN		207
#define SLAPI_PLUGIN_DB_ABANDON_FN		208
#define SLAPI_PLUGIN_DB_CONFIG_FN		209
#define SLAPI_PLUGIN_CLOSE_FN			210
#define SLAPI_PLUGIN_DB_FLUSH_FN		211
#define SLAPI_PLUGIN_START_FN			212
#define SLAPI_PLUGIN_DB_SEQ_FN			213
#define SLAPI_PLUGIN_DB_ENTRY_FN		214
#define SLAPI_PLUGIN_DB_REFERRAL_FN		215
#define SLAPI_PLUGIN_DB_RESULT_FN		216
#define SLAPI_PLUGIN_DB_LDIF2DB_FN		217
#define SLAPI_PLUGIN_DB_DB2LDIF_FN		218
#define SLAPI_PLUGIN_DB_BEGIN_FN		219
#define SLAPI_PLUGIN_DB_COMMIT_FN		220
#define SLAPI_PLUGIN_DB_ABORT_FN		221
#define SLAPI_PLUGIN_DB_ARCHIVE2DB_FN		222
#define SLAPI_PLUGIN_DB_DB2ARCHIVE_FN		223
#define SLAPI_PLUGIN_DB_NEXT_SEARCH_ENTRY_FN	224
#define SLAPI_PLUGIN_DB_FREE_RESULT_SET_FN	225
#define	SLAPI_PLUGIN_DB_SIZE_FN			226
#define	SLAPI_PLUGIN_DB_TEST_FN			227


/*  functions pointers for LDAP V3 extended ops */
#define SLAPI_PLUGIN_EXT_OP_FN			300
#define SLAPI_PLUGIN_EXT_OP_OIDLIST		301

/* functions for preoperation functions */
#define SLAPI_PLUGIN_PRE_BIND_FN		401
#define SLAPI_PLUGIN_PRE_UNBIND_FN		402
#define SLAPI_PLUGIN_PRE_SEARCH_FN		403
#define SLAPI_PLUGIN_PRE_COMPARE_FN		404
#define SLAPI_PLUGIN_PRE_MODIFY_FN		405
#define SLAPI_PLUGIN_PRE_MODRDN_FN		406
#define SLAPI_PLUGIN_PRE_ADD_FN			407
#define SLAPI_PLUGIN_PRE_DELETE_FN		408
#define SLAPI_PLUGIN_PRE_ABANDON_FN		409
#define SLAPI_PLUGIN_PRE_ENTRY_FN		410
#define SLAPI_PLUGIN_PRE_REFERRAL_FN		411
#define SLAPI_PLUGIN_PRE_RESULT_FN		412

/*  functions for postoperation functions*/
#define SLAPI_PLUGIN_POST_BIND_FN		501
#define SLAPI_PLUGIN_POST_UNBIND_FN		502
#define SLAPI_PLUGIN_POST_SEARCH_FN		503
#define SLAPI_PLUGIN_POST_COMPARE_FN		504
#define SLAPI_PLUGIN_POST_MODIFY_FN		505
#define SLAPI_PLUGIN_POST_MODRDN_FN		506
#define SLAPI_PLUGIN_POST_ADD_FN		507
#define SLAPI_PLUGIN_POST_DELETE_FN		508
#define SLAPI_PLUGIN_POST_ABANDON_FN		509
#define SLAPI_PLUGIN_POST_ENTRY_FN		510
#define SLAPI_PLUGIN_POST_REFERRAL_FN		511
#define SLAPI_PLUGIN_POST_RESULT_FN		512

/* audit plugin defines */
#define SLAPI_PLUGIN_AUDIT_DATA                1100
#define SLAPI_PLUGIN_AUDIT_FN                  1101

/* managedsait control */
#define SLAPI_MANAGEDSAIT       		1000

/* config stuff */
#define SLAPI_CONFIG_FILENAME			40
#define SLAPI_CONFIG_LINENO			41
#define SLAPI_CONFIG_ARGC			42
#define SLAPI_CONFIG_ARGV			43

/*  operational params */
#define SLAPI_TARGET_DN				50
#define SLAPI_REQCONTROLS			51

/* server LDAPv3 controls  */
#define SLAPI_RESCONTROLS			55
#define SLAPI_ADD_RESCONTROL			56	

/* add params */
#define SLAPI_ADD_TARGET			SLAPI_TARGET_DN
#define SLAPI_ADD_ENTRY				60

/* bind params */
#define SLAPI_BIND_TARGET			SLAPI_TARGET_DN
#define SLAPI_BIND_METHOD			70
#define SLAPI_BIND_CREDENTIALS			71	
#define SLAPI_BIND_SASLMECHANISM		72	
#define SLAPI_BIND_RET_SASLCREDS		73	

/* compare params */
#define SLAPI_COMPARE_TARGET			SLAPI_TARGET_DN
#define SLAPI_COMPARE_TYPE			80
#define SLAPI_COMPARE_VALUE			81

/* delete params */
#define SLAPI_DELETE_TARGET			SLAPI_TARGET_DN

/* modify params */
#define SLAPI_MODIFY_TARGET			SLAPI_TARGET_DN
#define SLAPI_MODIFY_MODS			90

/* modrdn params */
#define SLAPI_MODRDN_TARGET			SLAPI_TARGET_DN
#define SLAPI_MODRDN_NEWRDN			100
#define SLAPI_MODRDN_DELOLDRDN			101
#define SLAPI_MODRDN_NEWSUPERIOR		102	/* v3 only */

/* search params */
#define SLAPI_SEARCH_TARGET			SLAPI_TARGET_DN
#define SLAPI_SEARCH_SCOPE			110
#define SLAPI_SEARCH_DEREF			111
#define SLAPI_SEARCH_SIZELIMIT			112
#define SLAPI_SEARCH_TIMELIMIT			113
#define SLAPI_SEARCH_FILTER			114
#define SLAPI_SEARCH_STRFILTER			115
#define SLAPI_SEARCH_ATTRS			116
#define SLAPI_SEARCH_ATTRSONLY			117

/* abandon params */
#define SLAPI_ABANDON_MSGID			120

/* extended operation params */
#define SLAPI_EXT_OP_REQ_OID			160
#define SLAPI_EXT_OP_REQ_VALUE		161	

/* extended operation return codes */
#define SLAPI_EXT_OP_RET_OID			162	
#define SLAPI_EXT_OP_RET_VALUE		163	

#define SLAPI_PLUGIN_EXTENDED_SENT_RESULT	-1

#define SLAPI_BIND_SUCCESS		0
#define SLAPI_BIND_FAIL			2
#define SLAPI_BIND_ANONYMOUS		3

/* Search result params */
#define SLAPI_SEARCH_RESULT_SET			193
#define	SLAPI_SEARCH_RESULT_ENTRY		194
#define	SLAPI_NENTRIES				195
#define SLAPI_SEARCH_REFERRALS			196

#define SLAPI_OPERATION_AUTHTYPE                741
#define SLAPI_OPERATION_ID                      742
#define SLAPI_CONN_CERT                         743
#define SLAPI_CONN_AUTHMETHOD                   746

#define SLAPI_RESULT_CODE                       881
#define SLAPI_RESULT_TEXT                       882
#define SLAPI_RESULT_MATCHED                    883

/* filter types */
#ifndef LDAP_FILTER_AND
#define LDAP_FILTER_AND         0xa0L
#endif
#ifndef LDAP_FILTER_OR
#define LDAP_FILTER_OR          0xa1L
#endif
#ifndef LDAP_FILTER_NOT
#define LDAP_FILTER_NOT         0xa2L
#endif
#ifndef LDAP_FILTER_EQUALITY
#define LDAP_FILTER_EQUALITY    0xa3L
#endif
#ifndef LDAP_FILTER_SUBSTRINGS
#define LDAP_FILTER_SUBSTRINGS  0xa4L
#endif
#ifndef LDAP_FILTER_GE
#define LDAP_FILTER_GE          0xa5L
#endif
#ifndef LDAP_FILTER_LE
#define LDAP_FILTER_LE          0xa6L
#endif
#ifndef LDAP_FILTER_PRESENT
#define LDAP_FILTER_PRESENT     0x87L
#endif
#ifndef LDAP_FILTER_APPROX
#define LDAP_FILTER_APPROX      0xa8L
#endif
#ifndef LDAP_FILTER_EXT_MATCH
#define LDAP_FILTER_EXT_MATCH   0xa9L
#endif

int slapi_log_error( int severity, char *subsystem, char *fmt, ... );
#define SLAPI_LOG_FATAL                 0
#define SLAPI_LOG_TRACE                 1
#define SLAPI_LOG_PACKETS               2
#define SLAPI_LOG_ARGS                  3
#define SLAPI_LOG_CONNS                 4
#define SLAPI_LOG_BER                   5
#define SLAPI_LOG_FILTER                6
#define SLAPI_LOG_CONFIG                7
#define SLAPI_LOG_ACL                   8
#define SLAPI_LOG_SHELL                 9
#define SLAPI_LOG_PARSE                 10
#define SLAPI_LOG_HOUSE                 11
#define SLAPI_LOG_REPL                  12
#define SLAPI_LOG_CACHE                 13
#define SLAPI_LOG_PLUGIN                14
#define SLAPI_LOG_TIMING                15

#define SLAPI_PLUGIN_DESCRIPTION	12
typedef struct slapi_plugindesc {
        char    *spd_id;
        char    *spd_vendor;
        char    *spd_version;
        char    *spd_description;
} Slapi_PluginDesc;

#define SLAPI_PLUGIN_VERSION_01         "01"
#define SLAPI_PLUGIN_VERSION_02         "02"
#define SLAPI_PLUGIN_VERSION_03         "03"
#define SLAPI_PLUGIN_CURRENT_VERSION    SLAPI_PLUGIN_VERSION_03

#endif /* _SLAPI_PLUGIN_H */

