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

		this.edvDMRHead = ((EpiDataView)(this.oTrans.EpiDataViews["DMRHead"]));
		this.edvDMRHead.EpiViewNotification += new EpiViewNotification(this.edvDMRHead_EpiViewNotification);
		// End Wizard Added Variable Initialization

        edvDMRHead = ((EpiDataView)(oTrans.EpiDataViews["DMRHead"]));
    
	    DMRHead_Column.ColumnChanged += DMRHead_AfterFieldChange;
	    DMRHead_Column.ColumnChanging += DMRHead_BeforeFieldChange;

		// Begin Wizard Added Custom Method Calls

		this.btnUpDate.Click += new System.EventHandler(this.btnUpDate_Click);
		this.btnReset.Click += new System.EventHandler(this.btnReset_Click);
		this.btnRemove.Click += new System.EventHandler(this.btnRemove_Click);
		this.btnSend.Click += new System.EventHandler(this.btnSend_Click);
		this.btnADD.Click += new System.EventHandler(this.btnADD_Click);
		this.epiUltraComboC1_EmailTemplates.ValueChanged += new System.EventHandler(this.epiUltraComboC1_EmailTemplates_ValueChanged);
		this.epiBTRollUp.Click += new System.EventHandler(this.epiBTRollUp_Click);
		// End Wizard Added Custom Method Calls
		//AvailUsers, AlertList
		AvailUsers = new DataTable();
		AlertList = new DataTable();
		AvailUsers.Columns.Add("User", typeof(string));
		AlertList.Columns.Add("User", typeof(string));
		epiUGAvailUsers.DataSource = AvailUsers;
		epiUGAlertList.DataSource = AlertList;

		PopulateComboWithUserCodes(epiUltraComboC1_EmailTemplates, "DMREmail", "CodeID", "CodeDesc");
	}

	public void DestroyCustomCode()
	{
		// ** Wizard Insert Location - Do not delete 'Begin/End Wizard Added Object Disposal' lines **
		// Begin Wizard Added Object Disposal

		this.edvDMRHead.EpiViewNotification -= new EpiViewNotification(this.edvDMRHead_EpiViewNotification);
		this.edvDMRHead = null;
		this.btnUpDate.Click -= new System.EventHandler(this.btnUpDate_Click);
		this.btnReset.Click -= new System.EventHandler(this.btnReset_Click);
		this.btnRemove.Click -= new System.EventHandler(this.btnRemove_Click);
		this.btnSend.Click -= new System.EventHandler(this.btnSend_Click);
		this.btnADD.Click -= new System.EventHandler(this.btnADD_Click);
		this.epiUltraComboC1_EmailTemplates.ValueChanged -= new System.EventHandler(this.epiUltraComboC1_EmailTemplates_ValueChanged);
		this.epiBTRollUp.Click -= new System.EventHandler(this.epiBTRollUp_Click);
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


	private void edvDMRHead_EpiViewNotification(EpiDataView view, EpiNotifyArgs args)
	{
		// ** Argument Properties and Uses **
		// view.dataView[args.Row]["FieldName"]
		// args.Row, args.Column, args.Sender, args.NotifyType
		// NotifyType.Initialize, NotifyType.AddRow, NotifyType.DeleteRow, NotifyType.InitLastView, NotifyType.InitAndResetTreeNodes
		if ((args.NotifyType == EpiTransaction.NotifyType.Initialize))
		{
			if ((args.Row > -1))
			{
				decimal cost = ((decimal)edvDMRHead.dataView[edvDMRHead.Row]["AvgMtlUnitCost"] + (decimal)edvDMRHead.dataView[edvDMRHead.Row]["AvgLbrUnitCost"] + (decimal)edvDMRHead.dataView[edvDMRHead.Row]["AvgBurUnitCost"] + (decimal)edvDMRHead.dataView[edvDMRHead.Row]["AvgSubUnitCost"] + (decimal)edvDMRHead.dataView[edvDMRHead.Row]["AvgMtlBurUnitCost"]) * (decimal)edvDMRHead.dataView[edvDMRHead.Row]["DispTotDiscrepantQty"];
				txtTOTALCOST.Text = string.Format("{0}", cost);
				GetEmailListForReason_Vendor();
				epiShapeCFE.Visible = JobMtlSearch();
				epiShapeC1.Visible = epiShapeCFE.Visible;
			}
			else
			{
				lotnum = string.Empty;
			}
		}
	}
	string lotnum;
	private bool JobMtlSearch()
	{
		if((string)edvDMRHead.dataView[edvDMRHead.Row]["LotNum"] == string.Empty)return false;
		if(lotnum == (string)edvDMRHead.dataView[edvDMRHead.Row]["LotNum"])return epiShapeCFE.Visible;
		lotnum = (string)edvDMRHead.dataView[edvDMRHead.Row]["LotNum"];
		bool CFEResult = false;
		JobMtlSearchAdapter jms = new JobMtlSearchAdapter(this.oTrans);
		jms.BOConnect();
		bool MorePages;
		SearchOptions opts = new SearchOptions(SearchMode.AutoSearch);
		opts.NamedSearch.WhereClauses.Add("JobMtl", string.Format("(JobNum='{0}')", (string)edvDMRHead.dataView[edvDMRHead.Row]["LotNum"]));
		DataSet ds = jms.GetRows(opts, out MorePages);
		jms.Dispose();
		jms = null;
		PartAdapter p = new PartAdapter(this.oTrans);
		p.BOConnect();
		string partwhereclause = string.Empty;
		foreach(DataRow r in ds.Tables["JobMtl"].Rows)
		{
			partwhereclause += (partwhereclause.Length > 0 ? " OR ": "") + string.Format("PartNum='{0}'", (string)r["PartNum"]);
		}
		partwhereclause = string.Format("(({0}) and classid='CFE')", partwhereclause);
		SearchOptions sop = new SearchOptions(SearchMode.AutoSearch);
		sop.NamedSearch.WhereClauses.Add("Part", partwhereclause);
		DataSet pds = p.GetRows(sop, out MorePages);
		p.Dispose();
		p = null;
		CFEResult = pds.Tables["Part"].Rows.Count > 0;
		return CFEResult;
	}

	DataTable AvailUsers, AlertList;
	private void GetEmailListForReason_Vendor()
	{
		string ReasonCode = DMRReasonCode();//string.Empty;
		string VendorID = (string)edvDMRHead.dataView[edvDMRHead.Row]["VendorNumVendorID"];
		string ReasonType = "D";
		ReasonAdapter r = new ReasonAdapter(this.oTrans);
		r.BOConnect();
		r.GetByID(ReasonType, ReasonCode);
		string EmailList = string.Empty;
		switch(VendorID){
			case "FPICT":
					EmailList = (string)r.ReasonData.Tables["Reason"].Rows[0]["Character01"];
					break;
			case "FPITX":
					EmailList = (string)r.ReasonData.Tables["Reason"].Rows[0]["Character02"];
					break;
			case "FPIMX":
					EmailList = (string)r.ReasonData.Tables["Reason"].Rows[0]["Character03"];
					break;
			case "FPIUK":
					EmailList = (string)r.ReasonData.Tables["Reason"].Rows[0]["Character04"];
					break;
			case "FPIPL":
					EmailList = (string)r.ReasonData.Tables["Reason"].Rows[0]["Character05"];
					break;
			default:
					EmailList = (string)r.ReasonData.Tables["Reason"].Rows[0]["Character06"];
					break;
		}
		while(AvailUsers.Rows.Count > 0)AvailUsers.Rows[0].Delete();
		while(AlertList.Rows.Count > 0)AlertList.Rows[0].Delete();
		//EmailList = "abailey~bbaker~cmontiel~costeguin";
		foreach(string s in EmailList.Split('~')){
			if(s == string.Empty)continue;
			DataRow newuser = AvailUsers.NewRow();
			newuser["User"] = s;
			AvailUsers.Rows.Add(newuser);
		}
		string SelectedUsers = string.Empty;
		foreach(string s in ((string)edvDMRHead.dataView[edvDMRHead.Row]["Character10"]).Split('~'))
		{
			if(s == string.Empty)continue;
			DataRow newuser = AlertList.NewRow();
			newuser["User"] = s;
			if(SelectedUsers.Length > 0)SelectedUsers += "~";
			SelectedUsers += s;
			AlertList.Rows.Add(newuser);
		}
		foreach(string s in SelectedUsers.Split('~'))
		{
			if(s == string.Empty)continue;
			int i = 0;
			int selectedrow = 0;
			foreach(DataRow row in AvailUsers.Rows){
				i++;
				if(((string)row["User"]) == s)selectedrow = i;
			}
			if(selectedrow != 0)AvailUsers.Rows[selectedrow-1].Delete();
		}
		r.Dispose();
		r = null;
	}

	private void btnUpDate_Click(object sender, System.EventArgs args)
	{
		// ** Place Event Handling Code Here **
	}

	private void btnReset_Click(object sender, System.EventArgs args)
	{
		GetEmailListForReason_Vendor();
	}

	private void btnRemove_Click(object sender, System.EventArgs args)
	{
		string SelectedUsers = string.Empty;
		for(int i = 0; i < epiUGAlertList.Rows.Count; i++)
		{
			if(epiUGAlertList.Rows[i].Selected)
			{
				DataRow newuser = AvailUsers.NewRow();
				newuser["User"] = (string)epiUGAlertList.Rows[i].Cells[0].Value;
				if(SelectedUsers.Length > 0)SelectedUsers += "~";
				SelectedUsers += (string)epiUGAlertList.Rows[i].Cells[0].Value;
				AvailUsers.Rows.Add(newuser);
			}
		}
		foreach(string s in SelectedUsers.Split('~'))
		{
			if(s == string.Empty)continue;
			int i = 0;
			int selectedrow = 0;
			foreach(DataRow r in AlertList.Rows){
				i++;
				if(((string)r["User"]) == s)selectedrow = i;
			}
			if(selectedrow != 0)AlertList.Rows[selectedrow-1].Delete();
		}
		RefreshAlertList();
	}

	private string DMRReasonCode()
	{
		string ReasonCode = string.Empty;
		NonConfAdapter n = new NonConfAdapter(this.oTrans);
		n.BOConnect();
		bool MorePages;
		SearchOptions opts = new SearchOptions(SearchMode.AutoSearch);
		opts.NamedSearch.WhereClauses.Add("NonConf", string.Format("DMRNum={0}", (int)edvDMRHead.dataView[edvDMRHead.Row]["DMRNum"]));
		DataSet ds = n.GetRows(opts, out MorePages);
		foreach(DataRow r in ds.Tables["NonConf"].Rows)
		{
			ReasonCode = (string)r["ReasonCode"];
		};
		n.Dispose();
		n = null;
		return ReasonCode;
	}

	private void btnSend_Click(object sender, System.EventArgs args)
	{
		UserFileAdapter x = new UserFileAdapter(this.oTrans);
		x.BOConnect();
		bool MorePages;
		SearchOptions opts = new SearchOptions(SearchMode.AutoSearch);
		//Get dataset of all employees
		DataSet ds = x.GetRows(opts, out MorePages);
		string email = string.Empty;
		foreach(string s in ((string)edvDMRHead.dataView[edvDMRHead.Row]["Character10"]).Split('~'))
		{
			foreach(DataRow r in ds.Tables["UserFile"].Rows)
			{
				if((string)r["DCDUserID"] == s){
					if(email.Length > 0) email += ",";
					email += (string)r["EmailAddress"];
				}
			}
		}
		string sendEmailFromAddress = "epicor@franklinproducts.net";
		string sendEmailToAddress = email;
		string sendEmailSubject = string.Format("DMR {0}, Needs your attention!", (int)edvDMRHead.dataView[edvDMRHead.Row]["DMRNum"]);
		string sendEmailBody = txtBODY.Text;
		string sendEmailAttachment = string.Empty;
		//MessageBox.Show(string.Format("{0} - {1}", sendEmailToAddress, sendEmailBody));
		SendEmail(sendEmailFromAddress, sendEmailToAddress, sendEmailSubject, sendEmailBody, sendEmailAttachment);
	}

	public static void SendEmail(
                        string sendEmailFromAddress,
                        string sendEmailToAddress,
                        string sendEmailSubject,
                        string sendEmailBody,
                        string sendEmailAttachment) {
        MailAddress toEmail = new MailAddress(sendEmailToAddress);
        MailAddress fromEmail = new MailAddress(sendEmailFromAddress);

        MailMessage mail = new MailMessage(fromEmail, toEmail);

        mail.Subject = sendEmailSubject;
        mail.Body = sendEmailBody;
		if(sendEmailAttachment != string.Empty){
        System.Net.Mail.Attachment att = new System.Net.Mail.Attachment(sendEmailAttachment);
        mail.Attachments.Add(att);
		}

        SmtpClient smtpServer = new SmtpClient();

        // the email server Port. The default SMTP Port is 25 
        //TODO Determine the email server Port. An IT Administrator may provide this information
        smtpServer.Port = 25;

        // the email server address (e.g., "server.yourcomany.local"), 
        //TODO Determine the email server Host. An IT Administrator may provide this information
        smtpServer.Host = "fpimail";
        smtpServer.Send(mail);
    }

	private string GetUserCodeLongDesc(string TypeCodeID, string CodeID)
	{
		string LongDesc = string.Empty;
		UserCodesAdapter x = new UserCodesAdapter(this.oTrans);
		x.BOConnect();
		x.GetByID(TypeCodeID);
		foreach(DataRow r in x.UserCodesData.Tables["UDCodes"].Rows)
		{
			if((string)r["CodeID"] == CodeID)LongDesc = (string)r["LongDesc"];
		}
		x.Dispose();
		x = null;
		return LongDesc;
	}

	private DataTable CallDynamicQuery(string QueryID, string ParameterName, string ValueType, string ParameterValue)
	{
		DynamicQueryAdapter d = new DynamicQueryAdapter(this.oTrans);
		d.BOConnect();
		d.GetByID(QueryID);
		Epicor.Mfg.BO.QueryExecutionDataSet ds = d.GetQueryExecutionParameters(d.QueryDesignData);
		DataRow r = ds.Tables["ExecutionParameter"].NewRow();
		r["ParameterName"] = ParameterName;
		r["ParameterValue"] = ParameterValue;
		r["ValueType"] = ValueType;
		r["IsEmpty"] = false;
		r["RowIdent"] = string.Empty;
		r["RowMod"] = "A";
		ds.Tables["ExecutionParameter"].Rows.Add(r);
		string resultFieldList = string.Empty;
		int topNRecords = 0;
		bool hasMoreRecords;
		d.ExecuteByIDParametrized(QueryID, ds, "", topNRecords,out hasMoreRecords);
		DataTable ReturnDataTable = d.QueryResults.Tables["Results"];
		d.Dispose();
		d = null;
		return ReturnDataTable;
	}

	private void PopulateComboWithUserCodes(EpiUltraCombo c, string TypeCodeID, string ValueMember, string DisplayMember)
	{
		UserCodesAdapter x = new UserCodesAdapter(this.oTrans);
		x.BOConnect();
		x.GetByID(TypeCodeID);
		x.UserCodesData.Tables["UDCodes"].DefaultView.Sort = DisplayMember;
		c.DataSource = x.UserCodesData.Tables["UDCodes"];
		c.ValueMember = ValueMember;
		c.DisplayMember = DisplayMember;
		string[] fields = new string[]{DisplayMember};
		c.SetColumnFilter(fields);
		x.Dispose();
		x = null;
		
	}

	private void RefreshAlertList()
	{
		edvDMRHead.dataView[edvDMRHead.Row]["Character10"] = "";
		foreach(DataRow r in AlertList.Rows){
			if((string)edvDMRHead.dataView[edvDMRHead.Row]["Character10"] != string.Empty)edvDMRHead.dataView[edvDMRHead.Row]["Character10"] = (string)edvDMRHead.dataView[edvDMRHead.Row]["Character10"] + "~";
			edvDMRHead.dataView[edvDMRHead.Row]["Character10"] = (string)edvDMRHead.dataView[edvDMRHead.Row]["Character10"] + (string)r["User"];
		}
	}

	private void btnADD_Click(object sender, System.EventArgs args)
	{
		string SelectedUsers = string.Empty;
		for(int i = 0; i < epiUGAvailUsers.Rows.Count; i++)
		{
			if(epiUGAvailUsers.Rows[i].Selected)
			{
				DataRow newuser = AlertList.NewRow();
				newuser["User"] = (string)epiUGAvailUsers.Rows[i].Cells[0].Value;
				if(SelectedUsers.Length > 0)SelectedUsers += "~";
				SelectedUsers += (string)epiUGAvailUsers.Rows[i].Cells[0].Value;
				AlertList.Rows.Add(newuser);
			}
		}
		foreach(string s in SelectedUsers.Split('~'))
		{
			if(s == string.Empty)continue;
			int i = 0;
			int selectedrow = 0;
			foreach(DataRow r in AvailUsers.Rows){
				i++;
				if(((string)r["User"]) == s)selectedrow = i;
			}
			if(selectedrow != 0)AvailUsers.Rows[selectedrow-1].Delete();
		}
		RefreshAlertList();
	}


	private void epiUltraComboC1_EmailTemplates_ValueChanged(object sender, System.EventArgs args)
	{
		string emailbody = GetUserCodeLongDesc("DMREmail", (string)epiUltraComboC1_EmailTemplates.Value);
		emailbody = emailbody.Replace("<DMRNum>", ((int)edvDMRHead.dataView[edvDMRHead.Row]["DMRNum"]).ToString());
		emailbody = emailbody.Replace("<PartNum>", (string)edvDMRHead.dataView[edvDMRHead.Row]["PartNum"]);
		char[] c = new char[2];
		c[0] = Convert.ToChar(13);
		c[1] = Convert.ToChar(10);
		emailbody = emailbody.Replace(new string(c), Environment.NewLine);
		emailbody = emailbody.Replace("\r\n", Environment.NewLine);
		emailbody = emailbody.Replace("\n\r", Environment.NewLine);
		emailbody = emailbody.Replace("\r", Environment.NewLine);
		emailbody = emailbody.Replace("\n", Environment.NewLine);
		txtBODY.Text = emailbody;
	}

	private void epiBTRollUp_Click(object sender, System.EventArgs args)
	{
//		MessageBox.Show("your PN is " + (string)edvDMRHead.dataView[edvDMRHead.Row]["PartNum"]);

		DataTable partList = new DataTable();
		partList.Columns.Add("Company", typeof(string));
		partList.Columns.Add("Part", typeof(string));

		DataTable jobList = new DataTable();
		jobList.Columns.Add("Company", typeof(string));
		jobList.Columns.Add("JobNum", typeof(string));

		DataTable invList = new DataTable();
		invList.Columns.Add("Company", typeof(string));
		invList.Columns.Add("Whse", typeof(string));
		invList.Columns.Add("Part", typeof(string));
		invList.Columns.Add("OnHandQty", typeof(decimal));

		DataTable r = CallDynamicQuery("CIC68322-DMRMtlPartSearch", "MtlPartNum", "String", (string)edvDMRHead.dataView[edvDMRHead.Row]["PartNum"]);
//		DataTable r = CallDynamicQuery("CIC68322-DMRMtlPartSearch", "MtlPartNum", "String", epiTextBoxC1_TestPartNum.Text);
		foreach(DataRow row in r.Rows)
		{//00** FABRIC TEMPLATE

			if(partList.Select(string.Format("Company='{0}' and Part='{1}'", (string)row["Company"], (string)row["PartRev.PartNum"])).Length > 0)continue;
			DataRow nr = partList.NewRow();
			nr["Company"] = (string)row["Company"];
			nr["Part"] = (string)row["PartRev.PartNum"];
			partList.Rows.Add(nr);

			DataTable r1 = CallDynamicQuery("CIC68322-DMRJobSearchByPart", "PartNum", "String", (string)nr["Part"]);
			oTrans.PushStatusText("0.", true);
			foreach(DataRow row1 in r1.Rows)
			{
				if(jobList.Select(string.Format("Company='{0}' and JobNum='{1}'", (string)row1["Company"], (string)row1["JobHead.JobNum"])).Length > 0)continue;
				DataRow nr1 = jobList.NewRow();
				nr1["Company"] = (string)row1["Company"];
				nr1["JobNum"] = (string)row1["JobHead.JobNum"];
				jobList.Rows.Add(nr1);
			}

			DataTable r2 = CallDynamicQuery("CIC68322-DMRPartInventory", "PartNum", "String", (string)nr["Part"]);
			foreach(DataRow row1 in r2.Rows)
			{
				if(invList.Select(string.Format("Company='{0}' and Part='{1}' and Whse='{2}'", (string)row1["Company"], (string)row1["PartWhse.PartNum"], (string)row1["PartWhse.WarehouseCode"])).Length > 0)continue;
				DataRow nr2 = invList.NewRow();
				nr2["Company"] = (string)row1["Company"];
				nr2["Whse"] = (string)row1["PartWhse.WarehouseCode"];
				nr2["Part"] = (string)row1["PartWhse.PartNum"];
				nr2["OnHandQty"] = (decimal)row1["PartWhse.OnHandQty"];
				invList.Rows.Add(nr2);
			}
		}
		epiPartList.DataSource = partList;
		epiJobList.DataSource = jobList;
		epiInventory.DataSource = invList;
	}
}
