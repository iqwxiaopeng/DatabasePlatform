/*
 * SQLStatement.h
 * Definition of the structure used to build the syntax tree.
 */
#ifndef __STATEMENT_H__
#define __STATEMENT_H__

#include "Expr.h"
#include <vector>

namespace hsql {


typedef enum {
	kStmtError, // Unused
	kStmtSelect,
	kStmtInsert,
	kStmtUpdate,
	kStmtDelete,
	kStmtCreate,
	kStmtDrop,
	kStmtCreateDB,
	kStmtDropDB,
	kStmtUseDB,
	kStmtShowTable,
	kStmtDesc,
	kStmtCreateIndex,
	kStmtDropIndex
} StatementType;


/**
 * @struct SQLStatement
 * @brief Base class for every SQLStatement
 */
struct SQLStatement {
	SQLStatement(StatementType type) :
		_type(type) {};

	virtual ~SQLStatement() {}

	virtual StatementType type() { return _type; }

private:
	StatementType _type;
};


/**
 * @struct SQLStatementList
 * @brief Represents the result of the SQLParser. If parsing was successful it is a list of SQLStatement.
 */
struct SQLStatementList {
public:
	SQLStatementList() :
		isValid(true),
		parser_msg(NULL) {};

	SQLStatementList(SQLStatement* stmt) :
		isValid(true),
		parser_msg(NULL) {
		addStatement(stmt);	
	};
		
	 ~SQLStatementList() {
		for (std::vector<SQLStatement*>::iterator it = statements.begin(); it != statements.end(); ++it) {
			delete *it;
		}
		delete parser_msg;
	}

	void addStatement(SQLStatement* stmt) { statements.push_back(stmt); }
	SQLStatement* getStatement(int id) { return statements[id]; }
	size_t numStatements() { return statements.size(); }
	
	std::vector<SQLStatement*> statements;
	bool isValid;
	const char* parser_msg;
	int error_line;
	int error_col;
};



} // namespace hsql

#endif // __STATEMENT_H__
