#ifndef DB_EXECUTE_H_
#define DB_EXECUTE_H_

// 数据库操作类...
class DbExecute {
public:
	DbExecute();
	~DbExecute();

public:
	static int InitDb();
};

#endif // !DB_EXECUTE_H_