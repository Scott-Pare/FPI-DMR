// **************************************************
// Custom code for DMRProcessingForm
// Created: 8/28/2014 3:50:33 PM
// **************************************************
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Windows.Forms;
using Epicor.Mfg.BO;
using Epicor.Mfg.Core;
using Epicor.Mfg.Lib;
using Epicor.Mfg.UI;
using Epicor.Mfg.UI.Adapters;
using Epicor.Mfg.UI.Customization;
using Epicor.Mfg.UI.ExtendedProps;
using Epicor.Mfg.UI.FormFunctions;
using Epicor.Mfg.UI.FrameWork;
using Epicor.Mfg.UI.Searches;
using Infragistics.Win.UltraWinToolbars;
using Infragistics.Win.UltraWinGrid;
using System.Net.Mail;
using System.Reflection;

public class Script
{
	// ** Wizard Insert Location - Do Not Remove 'Begin/End Wizard Added Module Level Variables' Comments! **
	// Begin Wizard Added Module Level Variables **
	 
	    private EpiDataView edvDMRHead;
	// End Wizard Added Module Level Variables **

	// Add Custom Module Level Variables Here **

	public void InitializeCustomCode()
	{
		// ** Wizard Insert Location - Do not delete 'Begin/End Wizard Added Variable Initialization' lines **
		// Begin Wizard Added Variable Initialization

		// End Wizard Added Variable Initialization

        edvDMRHead = ((EpiDataView)(oTrans.EpiDataViews["DMRHead"]));
    
	    DMRHead_Column.ColumnChanged += DMRHead_AfterFieldChange;
	    DMRHead_Column.ColumnChanging += DMRHead_BeforeFieldChange;

		// Begin Wizard Added Custom Method Calls

		// End Wizard Added Custom Method Calls
	}

	public void DestroyCustomCode()
	{
		// ** Wizard Insert Location - Do not delete 'Begin/End Wizard Added Object Disposal' lines **
		// Begin Wizard Added Object Disposal

		// End Wizard Added Object Disposal

		// Begin Custom Code Disposal

		// End Custom Code Disposal
	}

private void DMRHead_BeforeFieldChange(object sender, DataColumnChangeEventArgs args) 
	{
        // ** Argument Properties and Uses **
        // args.Row["FieldName"]
        // args.Column, args.ProposedValue, args.Row
        // Add Event Handler Code
        switch (args.Column.ColumnName) 
		{
            case "CheckOff1":
            case "CheckOff2":
            case "CheckOff3":
            case "CheckOff4":
            case "CheckOff5":
            case "CheckBox01":
            case "CheckBox02":
            case "CheckBox03":
            case "CheckBox04":

                if (Convert.ToBoolean(args.ProposedValue) == false)
                    args.ProposedValue = true;
                break;
        }
    }

private void DMRHead_AfterFieldChange(object sender, DataColumnChangeEventArgs args) 
{
        // ** Argument Properties and Uses **
        // args.Row["FieldName"]
        // args.Column, args.ProposedValue, args.Row
        // Add Event Handler Code
        switch (args.Column.ColumnName)
		{
            case "CheckOff1":
            case "CheckOff2":
            case "CheckOff3":
            case "CheckOff4":
            case "CheckOff5":
            case "CheckBox01":
            case "CheckBox02":
            case "CheckBox03":
            case "CheckBox04":

                SetCheckBoxNotes(args);
            break;
        }
    }

	 private void SetCheckBoxNotes(DataColumnChangeEventArgs args)
	 {
        //  Store relationship between check boxes and note fields
        Dictionary<string, string> FieldRef = new Dictionary<string, string>();
     	   FieldRef.Add("CheckOff1", "ShortChar01");
     	   FieldRef.Add("CheckOff2", "ShortChar02");
     	   FieldRef.Add("CheckOff3", "ShortChar03");
     	   FieldRef.Add("CheckOff4", "ShortChar04");
     	   FieldRef.Add("CheckOff5", "ShortChar05");
     	   FieldRef.Add("CheckBox01", "ShortChar06");
     	   FieldRef.Add("CheckBox02", "ShortChar07");
        	FieldRef.Add("CheckBox03", "ShortChar08");
        	FieldRef.Add("CheckBox04", "ShortChar09");

        string ColumnName = args.Column.ColumnName;
        bool ProposedValue = Convert.ToBoolean(args.ProposedValue);
        if (ProposedValue && edvDMRHead.dataView[edvDMRHead.Row][FieldRef[ColumnName]].ToString() == "")
            edvDMRHead.dataView[edvDMRHead.Row][FieldRef[ColumnName]] = string.Format("{0}-{1}-{2} ", ((Session)oTrans.Session).UserID, DateTime.Now.ToShortTimeString(), DateTime.Today.ToString("dd-MMM-yy"));
        else if (!ProposedValue)
            edvDMRHead.dataView[edvDMRHead.Row][FieldRef[ColumnName]] = "";
    }

}
