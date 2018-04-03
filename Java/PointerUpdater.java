import java.io.BufferedReader;
import java.io.IOException;
import java.io.PrintStream;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.nio.file.StandardCopyOption;
import java.util.ArrayList;
import java.util.List;

public class PointerUpdater {
    class Variable {
		String name;
		String location;
	}
    
    List<String> cut(String string) { //Because I hate regex.!
    	List<String> list = new ArrayList<>();
    	int begin = -1;
    	for(int i = 0; i < string.length(); i++) {
    		if(begin == -1) {
    			if(!Character.isWhitespace(string.charAt(i))) {
    				begin = i;
    			}
    		} else {
    			if(Character.isWhitespace(string.charAt(i))) {
    				list.add(string.substring(begin, i));
    				begin = -1;
    			}
    		}
    	}
    	if(begin != -1) {
    		list.add(string.substring(begin));
    	}
    	return list;
    }
    
	List<Variable> variables; //Found variables
	
	public void loadVariables(String filename) {
		variables = new ArrayList<>();
		try (BufferedReader reader = Files.newBufferedReader(Paths.get(filename))) 
		{
		    String line = null;
		    while ((line = reader.readLine()) != null) {
		        List<String> words = cut(line);
		        if(words.size() == 2 && words.get(0).length() != 0 && words.get(1).length() == 4) {
		        	if(words.get(0).charAt(0) == '_') {
		        		Variable newVariable = new Variable();
		        		newVariable.name = words.get(0).substring(1);
		        		newVariable.location = words.get(1);
		        		variables.add(newVariable);
		        	}
		        }
		    }
		} catch (IOException e) {
			System.out.println("Couldn't load map!");
			System.exit(-1);
		}
	}
	
	Variable findVariable(String name) {
		for(Variable variable : variables) 
			if(name.equals(variable.name))
				return variable;
		
		return null;
	}
	final static String pointerHeader = "/*pointer";
	
	public void applyOnFile(String filename) {
		try {
			Files.copy(Paths.get(filename), Paths.get("backup/" + filename), StandardCopyOption.REPLACE_EXISTING);
			BufferedReader reader = Files.newBufferedReader(Paths.get(filename));
		    String line = null;
		    boolean hasFound = false;
		    List<String> fileContent = new ArrayList<>();
		    try {
		    while ((line = reader.readLine()) != null) {
		       String readLine = new String(line);
		       for(int i = 0; i < line.length() - pointerHeader.length(); i++) {
		    	   if(line.substring(i, i + pointerHeader.length()).equals(pointerHeader)) {
		    		   int variableEnd = i + pointerHeader.length();
		    		   while(line.charAt(variableEnd) != '*') //Searching for *, that ends variable name
			    			variableEnd++;
		    		   
			    	   Variable variable = findVariable(line.substring(i + pointerHeader.length(), variableEnd));
			    	   if(variable == null) {
			    		   System.out.println("Variable " + line.substring(i + pointerHeader.length(), variableEnd) + " not found!");
			    		   continue;
			    	   }
			    	   
			    	   int firstComa = i; //Finding a coma
			    	   for(int k = 0; k < 2; k++) {
			    		   firstComa--;
			    		
			    	   while(line.charAt(firstComa) != ',')
			    		   firstComa--;
			    	   }
			    	   
			    	   line = line.substring(0, firstComa+1) +  //Composing the line
			    			   " 0x" + variable.location.substring(2, 4) + "U," + //Cutting into two halves is all I need
			    			   " 0x" + variable.location.substring(0, 2) + "U/*pointer" + //Because the location is in hex(2B) and I write
			    			   line.substring(i + pointerHeader.length()); //In hex(1B) <3
		    		
			    	   i = variableEnd;
			    	   if(!line.equals(readLine))
			    		   hasFound = true;
		    		}
		       }
		       fileContent.add(line); //Adding the line to the list
		    }
		    reader.close();
		    if(hasFound) {
		    	PrintStream writer = new PrintStream(filename);
		    	for(String string : fileContent) {
		    		writer.println(string);
		    	}
		    	writer.close();
		    } }
		    catch(Exception ex) {
		    	System.out.println("Some exception happened: " + ex.getMessage());
		    	System.out.println("Line: " + line + "!");
		    }
		} catch (IOException x) {
			System.out.println("Couldn't find " + filename + " or the backup folder doesn't exist!");
			return;
		}
	}
	
	public void showRegisteredVariables() {
		System.out.println("Registered variables and functions: ");
		for(Variable variable : variables) {
			System.out.println("\t" +variable.name + " - 0x" + variable.location);
		}
	}
	
	public static void main(String[] string) {
		PointerUpdater updater = new PointerUpdater();
		if(string.length == 0) {
			System.out.println("Help: first argument is a .map file, every else is a file to apply the updater on. Backups are made in /backup/ directory(must exist!).");
			return;
		}
		updater.loadVariables(string[0]);
		for(int i = 1; i < string.length; i++) {
			updater.applyOnFile(string[i]);
		}
	}
}
