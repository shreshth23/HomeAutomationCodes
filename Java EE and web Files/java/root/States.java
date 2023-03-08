package root;

import java.io.IOException;
import java.io.PrintWriter;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import com.google.gson.Gson;

@WebServlet("/States")
public class States extends HttpServlet {
	private static final long serialVersionUID = 1L;
  
    public States() {
        super();
    }

	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		PrintWriter out =response.getWriter();
		String json = new Gson().toJson(new sendData());
		response.setContentType("application/json");
		response.setCharacterEncoding("UTF-8");
		out.print(json);
		out.flush();
	}


	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		doGet(request, response);
	}

}
class sendData{
	private int D0;
	private int D1;
	private int D2;
	private int D6;
	private int D4;
	private int D5;
	
	private int A0;
	
	private String temp;
	private String humd;
	
	public sendData() {
		this.D0 = Items.get("D0");
		this.D1 = Items.get("D1");
		this.D2 = Items.get("D2");
		this.D6 = Items.get("D6");
		this.D4 = Items.get("D4");
		this.D5 = Items.get("D5");
		
		this.A0 = Items.get("A0");

		this.temp = Items.getVal("temp");
		this.humd = Items.getVal("humd");
	}
}