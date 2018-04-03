package gbhelper.DatabaseManager;

import java.io.Serializable;

public interface Data extends Serializable {
	public Data construct(String[] values); //Able to construct on dummy object - no static in interfaces!
	public String[] getValues();
}
