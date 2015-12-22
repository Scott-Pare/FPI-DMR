// **************************************************
// Custom code for ReasonForm
// Created: 10/7/2015 12:38:05 PM
// **************************************************
using System;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Windows.Forms;
using Epicor.Mfg.BO;
using Epicor.Mfg.Core;
using Epicor.Mfg.UI;
using Epicor.Mfg.UI.Adapters;
using Epicor.Mfg.UI.Customization;
using Epicor.Mfg.UI.ExtendedProps;
using Epicor.Mfg.UI.FormFunctions;
using Epicor.Mfg.UI.FrameWork;
using Epicor.Mfg.UI.Searches;
using Epicor.Mfg.Lib;
using System.Collections.Generic;
using Infragistics.Win.UltraWinToolbars;
using Infragistics.Win.UltraWinGrid;
using System.Reflection;


public class Script
{
	// ** Wizard Insert Location - Do Not Remove 'Begin/End Wizard Added Module Level Variables' Comments! **
	// Begin Wizard Added Module Level Variables **
	private EpiDataView edvReasonData;

	private EpiDataView edvReasonDetail;
	// End Wizard Added Module Level Variables **
	Epicor.Mfg.Core.Session session;
	// Add Custom Module Level Variables Here **
	private List<string> selUsers = new List<string>();

	public void InitializeCustomCode()
	{
		// ** Wizard Insert Location - Do not delete 'Begin/End Wizard Added Variable Initialization' lines **
		// Begin Wizard Added Variable Initialization

		this.edvReasonDetail = ((EpiDataView)(this.oTrans.EpiDataViews["ReasonDetail"]));
		this.edvReasonDetail.EpiViewNotification += new EpiViewNotification(this.edvReasonDetail_EpiViewNotification);
		// End Wizard Added Variable Initialization

		// Begin Wizard Added Custom Method Calls
		session = (Epicor.Mfg.Core.Session)ReasonForm.Session;
		this.btnLOAD.Click += new System.EventHandler(this.btnLOAD_Click);
		this.btnCTADD.Click += new System.EventHandler(this.btnCTADD_Click);
		// End Wizard Added Custom Method Calls
	}

	public void DestroyCustomCode()
	{
		// ** Wizard Insert Location - Do not delete 'Begin/End Wizard Added Object Disposal' lines **
		// Begin Wizard Added Object Disposal

		this.btnLOAD.Click -= new System.EventHandler(this.btnLOAD_Click);
		this.btnCTADD.Click -= new System.EventHandler(this.btnCTADD_Click);
		this.edvReasonDetail.EpiViewNotification -= new EpiViewNotification(this.edvReasonDetail_EpiViewNotification);
		this.edvReasonDetail = null;
		// End Wizard Added Object Disposal

		// Begin Custom Code Disposal

		// End Custom Code Disposal
	}

	private void btnLOAD_Click(object sender, System.EventArgs args)
	{
		// ** Place Event Handling Code Here **
	
		QueryDesignDataSet dataset = new QueryDesignDataSet();
		DynamicQuery query = new DynamicQuery(session.ConnectionPool);
		dataset = query.GetByID("CIC68322-DMRUsers");
		//dataset.QueryWhereItem[0].RValue = 123;
		//DataTable table = query.Execute(dataset).Tables["Results"];
		epiDmrUserList.DataSource = query.Execute(dataset).Tables["Results"];
	
	}

	private void btnCTADD_Click(object sender, System.EventArgs args)
	{
		if(edvReasonDetail.Row == -1){
			MessageBox.Show("Please load a reason first");
			return;
		}
        foreach (UltraGridRow row in epiDmrUserList.Selected.Rows)
		{
			DataRow r = DMR_CT.NewRow();
			r["Email"] = row.Cells[0].Value.ToString();
			DMR_CT.Rows.Add(r);
		}
        String catUsers = "";
        foreach (DataRow r in DMR_CT.Rows)
		{
            if (((string)r["Email"]).Length > 0){
                catUsers += (string)r["Email"] + "~";
			}
		}
        edvReasonDetail.dataView[edvReasonDetail.Row]["Character01"] = catUsers;

    }


DataTable DMR_CT;
	private void edvReasonDetail_EpiViewNotification(EpiDataView view, EpiNotifyArgs args)
	{
		// ** Argument Properties and Uses **
		// view.dataView[args.Row]["FieldName"]
		// args.Row, args.Column, args.Sender, args.NotifyType
		// NotifyType.Initialize, NotifyType.AddRow, NotifyType.DeleteRow, NotifyType.InitLastView, NotifyType.InitAndResetTreeNodes
		if ((args.NotifyType == EpiTransaction.NotifyType.Initialize))
		{
			if ((args.Row > -1))
			{
				DMR_CT = new DataTable();
				if(DMR_CT.Columns.Count == 0){
					using (DataColumn dc = new DataColumn()) { dc.ColumnName = "Email"; dc.DataType=typeof(string); DMR_CT.Columns.Add(dc); }
				}
				foreach(string e in ((string)edvReasonDetail.dataView[edvReasonDetail.Row]["Character01"]).Split('~'))
				{
					if(e == string.Empty)continue;
					DataRow r = DMR_CT.NewRow();
					r["Email"] = e;
					DMR_CT.Rows.Add(r);
				}
				epiDMR_CT.DataSource = DMR_CT;
			//set grid box datasource
//pull in string
//split string
//insert records into table?
//set grid datasource to table
			}
		}
	}
}
