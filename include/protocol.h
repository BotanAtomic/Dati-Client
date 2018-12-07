//
// Created by Botan on 27/10/18.
//

#ifndef DATI_PROTOCOL_H
#define DATI_PROTOCOL_H

#include "client.h"
#include "query.h"
#include "list.h"

/** @Message_id : 0 **
 *  @Response : unsigned char : SUCCESS(1)/FAILED(0)
**/
unsigned char login(client *client);


/*** DATABASES **/
/** @Message_id : 1 **
 *  @Response : *char[] : list of databases
**/
list *getDatabases(client *client);

/** @Message_id : 2 **
 *  @Response : unsigned char : SUCCESS(1)/FAILED(0) & unsigned char : error_code
**/
unsigned char createDatabase(client *client, char *name);

/** @Message_id : 3 **
 *  @Response : unsigned char : SUCCESS(1)/FAILED(0) & unsigned char : error_code
**/
unsigned char removeDatabase(client *client, char *name);

/** @Message_id : 4 **
 *  @Response : unsigned char : SUCCESS(1)/FAILED(0) & unsigned char : error_code
**/
unsigned char renameDatabase(client *client, char *database, char *new_name);


/*** TABLES ***/
/** @Message_id : 5 **
 *  @Response : *char[] : list of tables of specified database
**/
list *getTables(client *client, char *database);

/** @Message_id : 6 **
 *  @Response : unsigned char : SUCCESS(1)/FAILED(0) & unsigned char : error_code
**/
unsigned char createTable(client *client, char *database, char *name);

/** @Message_id : 7 **
 *  @Response : unsigned char : SUCCESS(1)/FAILED(0) & unsigned char : error_code
**/
unsigned char removeTable(client *client, char *database, char *name);

/** @Message_id : 8 **
 *  @Response : unsigned char : SUCCESS(1)/FAILED(0) & unsigned char : error_code
**/
unsigned char renameTable(client *client, char *database, char *last_name, char *new_name);


/*** QUERY ***/
/** @Message_id : 9 **
 *  @_uuid : unique id of inserted statement
*  @Response : insert_result { @_uuid, @error_code }
**/
insert_result insertValue(client *client, char *database, char *table, list *insert_query);

#endif //DATI_PROTOCOL_H
