//
// Created by Botan on 27/10/18.
//

#ifndef DATI_PROTOCOL_H
#define DATI_PROTOCOL_H

#define ASYNC 1
#define SYNC 0

#include "client.h"
#include "query.h"
#include "list.h"
#include "node.h"



/** @Message_id : 0 **
 *  @Response : unsigned char : SUCCESS(1)/FAILED(0)
**/
unsigned char login(Client *client);


/*** DATABASES **/

/** @Message_id : 1 **
 *  @Response : *char[] : List of databases
**/
List *getDatabases(Client *client);

/** @Message_id : 2 **
 *  @Response : unsigned char : SUCCESS(1)/FAILED(0) & unsigned char : error_code
**/
unsigned char createDatabase(Client *client, char *name);

/** @Message_id : 3 **
 *  @Response : unsigned char : SUCCESS(1)/FAILED(0) & unsigned char : error_code
**/
unsigned char removeDatabase(Client *client, char *name);

/** @Message_id : 4 **
 *  @Response : unsigned char : SUCCESS(1)/FAILED(0) & unsigned char : error_code
**/
unsigned char renameDatabase(Client *client, char *database, char *new_name);


/*** TABLES ***/

/** @Message_id : 5 **
 *  @Response : *char[] : List of tables of specified database
**/
List *getTables(Client *client, char *database);

/** @Message_id : 6 **
 *  @Response : unsigned char : SUCCESS(1)/FAILED(0) & unsigned char : error_code
**/
unsigned char createTable(Client *client, char *database, char *name);

/** @Message_id : 7 **
 *  @Response : unsigned char : SUCCESS(1)/FAILED(0) & unsigned char : error_code
**/
unsigned char removeTable(Client *client, char *database, char *name);

/** @Message_id : 8 **
 *  @Response : unsigned char : SUCCESS(1)/FAILED(0) & unsigned char : error_code
**/
unsigned char renameTable(Client *client, char *database, char *last_name, char *new_name);


/*** VALUES ***/

/** @Message_id : 9 **
 *  @_uuid : unique id of inserted statement
*  @Response : insert_result { @_uuid, @error_code }
**/
InsertResult insertValue(Client *client, char *database, char *table, List *insertQuery, char async);

/** @Message_id : 9 **
 *  @_uuid : unique id of inserted statement
*  @Response : insert_result { @_uuid, @error_code }
**/
List * find(Client *client, char *database, char *table, void (*callback)(TableValue *), char * filter);

#endif //DATI_PROTOCOL_H
