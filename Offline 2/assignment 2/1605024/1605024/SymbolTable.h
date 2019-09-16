#include<bits/stdc++.h>
using namespace std;


FILE *logFile;
FILE *tokenFile;

int scopeTableID , roID , colID;

class symbolInfo {

private:
	string name , type;

public:
	symbolInfo* nextSymbol;


    symbolInfo() {
		name = "";
		type = "";
        nextSymbol = NULL;
    }
    symbolInfo(string symbolName , string symbolType) {

		name = symbolName;
		type = symbolType;
		nextSymbol = NULL;
    }

    void setName(const string &symbolName) {
    	name = symbolName;
    }

    string getName() {
    	return name;
    }

    void setType(const string &symbolType) {
    	type = symbolType;
    }

    string getType() {
    	return type;
    }

    ~symbolInfo() {
    	nextSymbol = NULL;
		delete nextSymbol;
    }
};



class scopeTable {

private:
    symbolInfo** ara;
    int id , len;


public:
	static int unique_ID;

	scopeTable* parentScope;

    scopeTable(int n) {

		len = n;

    	ara = new symbolInfo*[n];
		for(int i =0 ; i < n ; i++ ) ara[i] = NULL;

        parentScope = NULL;
        id = ++unique_ID;
    }


    int getHash(const string& name) {

        int sum = 0;
        int prime = 23 , mod = 97;
        int prod = 1;

        for(int i =0 ; i < name.size() ; i++ ) {

            sum = (sum + name[i]* prod) %len;
            prod = (prod * prime)% mod;
        }
        return sum;
    }

    bool Insert(const string& name ,const string& type) {

        int headID = getHash(name);

        scopeTableID = id;
        roID = headID;
        colID = 0;


        symbolInfo* node = new symbolInfo(name , type);


        symbolInfo* head  = ara[headID];


        if( head == NULL ) {
            ara[headID] = node;
            return true;
        }

        if( head->getName() == name) return false;
        colID++;

        while( head->nextSymbol != NULL) {
			head = head ->nextSymbol;
			colID++;
			if( head->getName() == name) return false;
        }

        head->nextSymbol = node;


        return true;
    }

    symbolInfo* Lookup(const string& keyName) {

		int headID = getHash(keyName);
		scopeTableID = id;
		roID = headID;
		colID = 0;


        symbolInfo* head  = ara[headID];

        while( head != NULL) {

            if( head->getName() == keyName) return head;
            head = head->nextSymbol;
            colID++;
        }

        return NULL;
    }

    bool Delete(const string& keyName) {

		int headID = getHash(keyName);
        scopeTableID = id;
        roID = headID;
        colID = 0;

        symbolInfo* head  = ara[headID];

        if( head == NULL ) return false;

        if( head->getName() == keyName) {

            ara[headID] = head->nextSymbol;
            delete head;
            return true;
        }
        colID++;

        while( head->nextSymbol != NULL) {

			if( head->nextSymbol->getName() == keyName ) {

                symbolInfo* node = head->nextSymbol;
                head->nextSymbol = node->nextSymbol;
                delete node;
                return true;
			}
            head = head->nextSymbol;
            colID++;
        }

        return false;
    }


	void Print() {
        fprintf(logFile, "\tScopeTable # %d\n", id);
        for(int i =0 ; i < len ; i++ ) {


            symbolInfo* head = ara[i];
            if( head == NULL ) continue;

            fprintf(logFile, "\t%d --> ", i);


            while( head != NULL ) {
                fprintf(logFile, "<%s, %s> ",head->getName().c_str() , head->getType().c_str() );
                head = head->nextSymbol;
            }
            fprintf(logFile, "\n" );
        }
        fprintf(logFile, "\n" );
	}

	void Erase(symbolInfo* node) {
        if( node == NULL )return;
        Erase(node->nextSymbol);
        delete node;
	}


	~scopeTable() {
        for(int i =0 ; i < len ; i++ )
            Erase(ara[i]);

        delete []ara;
        parentScope = NULL;
        delete parentScope ;
	}
};


class symbolTable {

private:

    scopeTable* current;
    int tableSize;

public:
    symbolTable(int n) {

		current = new scopeTable(n);
		tableSize = n;
    }

    void enterScope() {

        scopeTable* node = new scopeTable(tableSize);
        node->parentScope = current;
        current = node;
    }

    void exitScope() {


        scopeTable* node = current;

        current = current->parentScope;
        delete node;
    }

    bool Insert(const string&name ,const string&type) {
		return current->Insert(name , type);
    }

    bool Remove(const string& keyName) {
    	return current->Delete(keyName);
    }

    symbolInfo* Lookup(const string& keyName) {

        scopeTable* table = current;

        while(table != NULL ) {

            symbolInfo* node = table->Lookup(keyName);
            if( node!= NULL) return node;
            table = table->parentScope;
        }
		return NULL;
    }

    void printCurrent() {

        current->Print();
    }

    void printAll() {

		scopeTable* table = current;
        while( table != NULL ) {
			table->Print();
			table = table->parentScope;
        }
    }

    ~symbolTable() {
    	delete current;
    }


};

int scopeTable::unique_ID  = 0;

// int main()
// {
// //	freopen("input.txt" , "r" , stdin);
// //	freopen("output.txt" , "w"  , stdout);
// 	int n;
// 	cin>>n;
// 	symbolTable table(n);

// 	string ch;

//     while(cin>>ch) {
//         cout<<endl<<ch<<" ";

//         if( ch == "I") {

//             string name , type;
//             cin>>name >> type;
//             cout<<name<<" "<<type<<endl<<endl;

//             bool ok = table.Insert(name, type);

// 			if( ok ) cout<<" Inserted in ScopeTable# "<<scopeTableID<<" at position "<<roID<<", "<<colID<<endl;
//             else cout<<" "<<name<<" already exists in current ScopeTable"<<endl;
//         }
//         else if(ch =="L") {

// 			string keyName;
// 			cin>>keyName;
// 			cout<<keyName<<endl<<endl;

// 			symbolInfo* node = table.Lookup(keyName);

// 			if( node == NULL) cout<<" Not Found"<<endl;
// 			else cout<<" Found in ScopeTable# "<<scopeTableID<<" at position "<<roID<<", "<<colID<<endl;
//         }
//         else if(ch == "D") {

// 			string keyName;
// 			cin>>keyName;
// 			cout<<keyName<<endl<<endl;

// 			bool ok = table.Remove(keyName);
// 			if( ok) {
// 				cout<<" Found in ScopeTable# "<<scopeTableID<<" at position "<<roID<<", "<<colID<<endl;
// 				cout<<" Deleted entry at "<<roID<<", "<<colID<<" from current ScopeTable"<<endl;
// 			}
// 			else cout<<" Not Found"<<endl;
//         }


//         else if( ch == "P") {
//             string ch1;
//             cin>>ch1;
//             cout<<ch1<<endl<<endl;

//             if( ch1 == "C") table.printCurrent();
//             else if( ch1 == "A") table.printAll();
//         }
//         else if( ch =="S") {

// 			cout<<endl;
//             table.enterScope();
//         }
//         else if( ch == "E")  {

// 			cout<<endl;
// 			table.exitScope();
//         }
//     }

//     return 0;
// }
