
void Compiler::emitSubtractionCode(string operand1, string operand2)    // op2 -  op1			
{
	
}

void Compiler::emitMultiplicationCode(string operand1, string operand2) // op2 *  op1			
{
	if (!isInteger(operand1) && !isInteger(operand2))
	{
		processError("illegal type");
	}
	if (isTemporary(contentsOfAReg) &&
		(contentsOfAReg != operand1) &&
		(contentsOfAReg != operand2))
	{
		string tempAInternalName = symbolTable.at(contentsOfAReg).getInternalName(); 
		emit("", "mov", "[" +  tempAInternalName + "], eax", contentsOfAReg + " = AReg");
		symbolTable.at(contentsOfAReg).setAlloc(YES);
		contentsOfAReg = "";
	}
	if (!isTemporary(contentsOfAReg) &&
		(contentsOfAReg != operand1) &&
		(contentsOfAReg != operand2))
	{
		contentsOfAReg = "";
	}
	if ((contentsOfAReg != operand1) &&
		(contentsOfAReg != operand2))
	{
		string internalName = symbolTable.at(operand2).getInternalName();
		emit("", "mov", "eax, [" + internalName + "]", "; load " + operand2 + "in eax");
		contentsOfAReg = operand2;		
	}
	string op1internalName = symbolTable.at(operand1).getInternalName();   
	string op2internalName = symbolTable.at(operand2).getInternalName(); 
	
	// emit code to perform register-memory multiplication
	if (operand1 != contentsOfAReg)
	{
		emit("", "imul", "dword [" + op1internalName + "]", "AReg = " + operand2 + " * " + operand1);
	}
	else
	{
		emit("", "imul", "dword [" + op2internalName + "]", "AReg = " + operand1 + " * " + operand2);
	}
	
	// deassign all temporaries involved in the addition and free those names for reuse
	if (isTemporary(operand1))
	{
		freeTemp();
	}
	if (isTemporary(operand2))
	{
		freeTemp();
	}

	/*
	A Register = next available temporary name and change type of its symbol table entry to integer
	push the name of the result onto operandStk
	*/
	contentsOfAReg = getTemp();
	symbolTable.at(contentsOfAReg).setDataType(INTEGER);
	pushOperand(contentsOfAReg);
}

void Compiler::emitDivisionCode(string operand1, string operand2)       // op2 /  op1			
{
	
}

void Compiler::emitModuloCode(string operand1, string operand2)         // op2 %  op1			
{
	
}

void Compiler::emitNegationCode(string operand1, string operand2)           // -op1					
{
	
}

void Compiler::emitNotCode(string operand1, string operand2)                // !op1
{
	
}

void Compiler::emitAndCode(string operand1, string operand2)            // op2 && op1			
{
	
}

void Compiler::emitOrCode(string operand1, string operand2)             // op2 || op1			
{
	
}

void Compiler::emitEqualityCode(string operand1, string operand2)       // op2 == op1			
{
	
}

void Compiler::emitInequalityCode(string operand1, string operand2)     // op2 != op1			
{
	
}

void Compiler::emitLessThanCode(string operand1, string operand2)       // op2 <  op1			
{
	
}

void Compiler::emitLessThanOrEqualToCode(string operand1, string operand2) // op2 <= op1		
{
	
}

void Compiler::emitGreaterThanCode(string operand1, string operand2)    // op2 >  op1			
{
	
}

void Compiler::emitGreaterThanOrEqualToCode(string operand1, string operand2) // op2 >= op1		
{
	
}



// ::

void Compiler::execStmts() // stage 1, production 2
{
   while (token != "end")
   {
      execStmt();
      nextToken();
   }
}


void Compiler::execStmt() // stage 1, production 3
{
	if (isNonKeyId(token))
	{
		assignStmt();
	}
	else if (token == "read")
	{
		readStmt();
	}
	else if (token == "write")
	{
		writeStmt();
	}
	else
	{
		processError("non-keyword identifier, \"read\", or \"write\" expected");
	}
}

void Compiler::assignStmt() // stage 1, production 4
{
	string popOperatorStr, popOperand1, popOperand2;

	if (isNonKeyId(token))
	{
		pushOperand(token);
	}
	nextToken();
	
	if (token != ":=")
	{
		processError("expected \":=\" for assignment statement");
	}
	pushOperand(token);
	nextToken();
	express();
	nextToken();
	
	if (token != ";")
	{
		processError("semicolon expected");
	}

	popOperatorStr = popOperator();
	popOperand1 = popOperand();
	popOperand2 = popOperand();
	code(popOperatorStr, popOperand1, popOperand2);
}

void Compiler::readStmt() // stage 1, production 5
{
	if (token != "read")
	{
		processError("keyword \"read\" expected");
	}
	nextToken();
	
	if (token != "(")
	{
		processError("\"(\" expected (for read statements)");
	}
	
	nextToken();
	string tempIDs = ids();
	nextToken();
	
	if (token != ")")
	{
		processError("\")\" expected");
	}
	
	code("read", tempIDs);
	nextToken();
	if (token != ";")
	{
		processError("semicolon expected");
	}
}

void Compiler::writeStmt() // stage 1, production 7
{
	if (token != "write")
	{
		processError("keyword \"write\" expected");
	}
	nextToken();
	
	if (token != "(")
	{
		processError("\"(\" expected (for write statements)");
	}
	
	// nextList
	nextToken();
	string tempIDs = ids();
	nextToken();
	
	if (token != ")")
	{
		processError("\")\" expected");
	}
	
	code("write", tempIDs);
	nextToken();
	if (token != ";")
	{
		processError("semicolon expected");
	}	
}

void Compiler::express() // stage 1, production 9
{
	term();
	expresses();
}

void Compiler::expresses() // stage 1, production 10
{
	if ((token == "<>") || (token == "=") || (token == "<=") || 
		(token == ">=") || (token == "<") || (token == ">"))
	{
		pushOperator(token);
		nextToken();
		term();
		
		string poppedOperator, poppedOperand1, poppedOperand2;
		
		poppedOperator = popOperator();
		poppedOperand1 = popOperand();
		poppedOperand2 = popOperand();
		code(poppedOperator, poppedOperand1, poppedOperand2);
		expresses();
	}
}

void Compiler::term() // stage 1, production 11
{
	factor();
   terms();
}

void Compiler::terms() // stage 1, production 12
{
   if (token == "+" || token == "-" || token == "or")
   {
      pushOperator(token);
      
      nextToken();
      factor();
      
      string poppedOperator, poppedOperand1, poppedOperand2;
      poppedOperator = popOperator();
		poppedOperand1 = popOperand();
		poppedOperand2 = popOperand();
		
      code(poppedOperator, poppedOperand1, poppedOperand2);
      
      terms();
   }
}

void Compiler::factor() // stage 1, production 13
{
	part();
	factors();
}

void Compiler::factors() // stage 1, production 14
{
   if (token == "*" || token == "div" || token == "mod" || token == "and")
   {
      pushOperator(token);

		nextToken();
		part();
      string poppedOperator, poppedOperand1, poppedOperand2; 
		
		poppedOperator = popOperator();
		poppedOperand1 = popOperand();
		poppedOperand2 = popOperand();
		
      code(poppedOperator, poppedOperand1, poppedOperand2);
      
      factors();
   }
}

void Compiler::part() // stage 1, production 15
{
	if ((token == "not"))
	{
		nextToken();
		if (token == "(")
		{
			nextToken();
			express();
			
			if (token != ")")
			{
				processError("no matching closing parenthesis");
			}
			// VALID / NEXT PART
			string poppedOperand = popOperand();
			code("not", poppedOperand);
			nextToken();
		}
		else if (isBoolean(token))
		{
			// VALID / NEXT PART	
			if (token == "true")
			{
				code("not", "true");
			}
			else
			{
				code("not", "false");
			}
			nextToken();
		}
		else if (isNonKeyId(token))
		{
			// VALID / NEXT PART	
			code("not", token);
			nextToken();
		}
		else
		{
			processError("non-keyword-identifier, boolean, or \"(\" expected after \"not\"");
		}
	}
	else if ((token == "+"))
	{
		nextToken();
		if (token == "(")
		{
			nextToken();
			express();
			if (token != ")")
			{
				processError("no matching closing parenthesis");
			}
			// VALID / NEXT PART
			nextToken();
		}
		else if (isInteger(token))
		{
			// VALID / NEXT PART
			pushOperand(token);
			nextToken();
		}
		else if (isNonKeyId(token))
		{
			// VALID / NEXT PART
			pushOperand(token);
			nextToken();
		}
		else
		{
			processError("integer expected after after \"+\""); 
		}
	}
	else if ((token == "-"))
	{
		nextToken();
		if (token == "(")
		{
			nextToken();
			express();
			
			if (token != ")")
			{
				processError("no matching closing parenthesis");
			}
			// VALID / NEXT PART
			code("neg", popOperand());
			nextToken();
		}
		else if (isLiteral(token) && isInteger(token))
		{
			// VALID / NEXT PART
			pushOperand("-" + token);
			nextToken();
		}
		else if (isNonKeyId(token))
		{
			// VALID / NEXT PART
			pushOperand("neg" + token);
			nextToken();
		}
		else
		{
			processError("integer expected after after \"-\""); 
		}
	}
	else if (token == "(")
	{
		nextToken();
		express();
		if (token != ")")
		{
			processError("no matching closing parenthesis");
		}
		// VALID / NEXT PART
		nextToken();
	}
	else if (isInteger(token) || isBoolean(token) || isNonKeyId(token))
	{
		// VALID / NEXT PART
		pushOperand(token);
	}
}

// ::

void Compiler::freeTemp()
{
    currentTempNo--;
    if (currentTempNo < -1)
    {
    	string err = "compiler error, " + to_string(currentTempNo) + "should be >= -1";
    	processError(err);
    }
}

string Compiler::getTemp()
{
  string temp;
  currentTempNo++;
  temp = "T" + to_string(currentTempNo);
  
  if (currentTempNo > maxTempNo)
  {
  	insert(temp, UNKNOWN, VARIABLE, "", NO, 1);
    maxTempNo++;
  }
  
	return temp;
}

string Compiler::getLabel()
{
	// FIXME: Finish
	return "";	
}

bool Compiler::isTemporary(string s) const // determines if s represents a temporary
{
  return (s[0] == 'T');
}


// Push and Pop
void Compiler::pushOperator(string name) //push name onto operatorStk
{
	operatorStk.push(name);
}

void Compiler::pushOperand(string name) //push name onto operandStk
{
  bool valid_condition = (isLiteral(name) && symbolTable.count(name));
  if (valid_condition)
  {
  	if (name == "true")
    {
    	insert("TRUE", BOOLEAN, CONSTANT, name, YES, 1);
    }
    else if (name == "false")
    {
    	insert("FALSE", BOOLEAN, CONSTANT, name, YES, 1);
    }
    else
    {
    	insert(name, whichType(name), CONSTANT, name, YES, 1);
    }
  }
  else if (!valid_condition)
  {
  	processError("reference to undefined symbol");
  }
  operandStk.push(name);
}

string Compiler::popOperator() //pop name from operatorStk
{
  if (!operatorStk.empty())
  {
	string op = operatorStk.top();
	operandStk.pop();
	return op;
  }
  processError("compiler error; operator stack underflow");
  return "";
}

string Compiler::popOperand() //pop name from operandStk
{
  if (!operandStk.empty())
  {
	string op = operandStk.top();
	operandStk.pop();
	return op;
  }
  processError("compiler error; operator stack underflow");
  return "";
}

// ::
