/*
 * record.h
 *
 *  Created on: Oct 21, 2018
 *      Author: meir
 */

#ifndef SRC_RECORD_H_
#define SRC_RECORD_H_

#include "redisgears.h"
#include "utils/buffer.h"
#include "utils/dict.h"
#ifdef WITHPYTHON
#include <Python.h>
#endif

enum AdditionalRecordTypes{
    STOP_RECORD = 8, // telling the execution plan to stop the execution.
#ifdef WITHPYTHON
    PY_RECORD
#endif
};

enum RecordAllocator{
    DEFAULT = 1,
    PYTHON
};

typedef struct KeysHandlerRecord{
    char* key;
}KeysHandlerRecord;

typedef struct LongRecord{
    long num;
}LongRecord;

typedef struct DoubleRecord{
    double num;
}DoubleRecord;

typedef struct StringRecord{
    size_t len;
    char* str;
}StringRecord;

typedef struct ListRecord{
    Record** records;
}ListRecord;

#ifdef WITHPYTHON
typedef struct PythonRecord{
    PyObject* obj;
}PythonRecord;
#endif

typedef struct KeyRecord{
    char* key;
    size_t len;
    Record* record;
}KeyRecord;

typedef struct HashSetRecord{
    dict* d;
}HashSetRecord;

typedef struct Record{
    union{
        KeysHandlerRecord keyHandlerRecord;
        LongRecord longRecord;
        StringRecord stringRecord;
        DoubleRecord doubleRecord;
        ListRecord listRecord;
        KeyRecord keyRecord;
        HashSetRecord hashSetRecord;
#ifdef WITHPYTHON
        PythonRecord pyRecord;
#endif
    };
    enum RecordType type;
}Record;

extern Record StopRecord;

int RG_RecordInit();
void RG_SetRecordAlocator(enum RecordAllocator allocator);
void RG_DisposeRecord(Record* record);
void RG_FreeRecord(Record* record);
enum RecordType RG_RecordGetType(Record* r);

/** key record api **/
Record* RG_KeyRecordCreate();
void RG_KeyRecordSetKey(Record* r, char* key, size_t len);
void RG_KeyRecordSetVal(Record* r, Record* val);
Record* RG_KeyRecordGetVal(Record* r);
char* RG_KeyRecordGetKey(Record* r, size_t* len);

/** list record api **/
Record* RG_ListRecordCreate(size_t initial_size);
size_t RG_ListRecordLen(Record* r);
void RG_ListRecordAdd(Record* r, Record* element);
Record* RG_ListRecordGet(Record* r, size_t index);
Record* RG_ListRecordPop(Record* r);

/** string record api **/
Record* RG_StringRecordCreate(char* val, size_t len);
char* RG_StringRecordGet(Record* r, size_t* len);
void RG_StringRecordSet(Record* r, char* val, size_t len);

/** double record api **/
Record* RG_DoubleRecordCreate(double val);
double RG_DoubleRecordGet(Record* r);
void RG_DoubleRecordSet(Record* r, double val);

/** long record api **/
Record* RG_LongRecordCreate(long val);
long RG_LongRecordGet(Record* r);
void RG_LongRecordSet(Record* r, long val);

/** hash set record api **/
Record* RG_HashSetRecordCreate();
int RG_HashSetRecordSet(Record* r, char* key, Record* val);
Record* RG_HashSetRecordGet(Record* r, char* key);
char** RG_HashSetRecordGetAllKeys(Record* r, size_t* len);
void RG_HashSetRecordFreeKeysArray(char** keyArr);

/* todo: think if we can removed this!! */
Record* RG_KeyHandlerRecordCreate(RedisModuleKey* handler);
RedisModuleKey* RG_KeyHandlerRecordGet(Record* r);

void RG_SerializeRecord(BufferWriter* bw, Record* r);
Record* RG_DeserializeRecord(BufferReader* br);

#ifdef WITHPYTHON
Record* RG_PyObjRecordCreate();
PyObject* RG_PyObjRecordGet(Record* r);
void RG_PyObjRecordSet(Record* r, PyObject* obj);
#endif




#endif /* SRC_RECORD_H_ */
