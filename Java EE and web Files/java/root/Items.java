package root;

import java.util.HashMap;

public class Items {
	static HashMap<String, Integer> state = new HashMap<String, Integer>();
	static HashMap<String, String> value = new HashMap<String, String>();
	
	static void initialize() {
		
		state.put("D0", 0);	//bulb1
		state.put("D1", 0);	//bulb2
		state.put("D2", 0);	//bulb3
		state.put("D6", 0);	//bulb4
		
		state.put("D4", 0);	//methane
		state.put("D5", 0);	//fire
		
		state.put("A0", 0); //LDR
		
		value.put("temp", "00"); //dht11 - temp
		value.put("humd", "00"); //dht11 - humd
		
		System.out.print("System Online...");
	}
	static void set(String key) {
		int data = state.get(key);
		data = (data+1)%2;
		state.put(key, data);
		System.out.println(key + " : " + data);
	}
	static int get(String key) {
		return state.get(key);
	}
	static String getVal(String key) {
		return value.get(key);
	}
	static void setVal(String key,String val) {
		value.put(key,val);
	}
}
