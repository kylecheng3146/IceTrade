using System;
using System.Collections.Generic;
using System.Collections;
using System.Windows.Forms;

namespace Order
{
    public class Order
    {
        //'委成回用到的欄位, 欄位說明請參照文件
        public const int KEY1 = 350;
        public const int KEY2 = 351;
        public const int FORM_TYPE = 352;
        public const int HEADER = 353;
        public const int FTR_NAME2 = 354;
        public const int MEMO = 355;
        public const int OKSEQNO = 356;
        public const int OD_PRICE2 = 357;
        public const int OD_QTY2 = 358;
        public const int BFR_QTY = 359;
        public const int AFT_QTY = 360;
        public const int FUNCTIONCODE = 361;
        public const int SRC_CODE = 362;
        public const int ORG_QTY2 = 363;
        public const int DEAL_QTY = 364;
        public const int DEAL_QTY2 = 365;
        public const int DEAL_AVGPRICE = 366;
        public const int TRANS_DATE = 159;
        public const int MATCH_TIME = 310;
        //'public const int  BRANCH_ID = 1;
        public const int ORDNO = 147;
        public const int S_OD_SEQ = 143;
        public const int F_OD_SEQ = 208;
        //'public const int  CUST_ID = 39;
        public const int STK_ID = 85;
        public const int FTR_ID = 114;
        public const int FTR_MTH = 115;
        public const int CALLPUT = 116;
        public const int STRIKE_PRICE = 117;
        public const int BUYSELL = 148;
        public const int FTR_ID2 = 130;
        public const int FTR_MTH2 = 131;
        public const int CALLPUT2 = 132;
        public const int STRIKE_PRICE2 = 133;
        public const int BUYSELL2 = 134;
        public const int PRICE_FLAG = 150;
        public const int OPENCLOSE = 163;
        public const int OD_TYPE = 149;
        //'public const int  AGENT_ID = 5;
        public const int ERR_CODE = 68;
        public const int ERR_MSG = 69;
        public const int OD_PRICE = 151;
        public const int OBOD_PRICE = 257;
        public const int OD_QTY = 156;
        public const int OD_KEY = 201;
        public const int F_ORG_SEQ = 204;
        public const int S_ORG_SEQ = 144;
        public const int MARKET_TYPE = 101;
        public const int TRADE_TYPE = 153;
        public const int STOP_PRICE = 219;
        public const int ORDER_KEY = 201;
        public const int EXCHANGE = 218;
        public const int DAY_TRADE = 220;


        //艾揚下單使用                 '  證券                    期貨         選擇權             複式
        public const int ORDER_ARGS_ROCID = 0;            //'X 身份證字號(登入帳號)           *             *               *
        public const int ORDER_ARGS_PASSWORD = 1;    //     'X 登入密碼                       *             *               *
        public const int ORDER_ARGS_BRANCHID = 2;        // 'X 分公司代號                     *             *               *
        public const int ORDER_ARGS_CUSTID = 3;           //X 帳號                           *             *               *
        public const int ORDER_ARGS_AGENTID = 4;          //X 營業員代碼                     *             *               *
        public const int ORDER_ARGS_SOURCE = 5;        //   'X 來源別                         *             *               *
        public const int ORDER_ARGS_ID = 6;               //'X 商品代碼                       *             *           (第一腳)代碼
        public const int ORDER_ARGS_BS = 7;               //'X 買賣別                         *             *           (第一腳)買賣別
        public const int ORDER_ARGS_ODTYPE = 8;        //   'X 現股(0)/融資(1)/融券(2)        ""      IOC(I)/ROD(R)/FOK(F)    *
        public const int ORDER_ARGS_TRADE_TYPE = 9;  //     'X 普通(N)/盤後(F)/零股(O)        ""            *               *
        public const int ORDER_ARGS_PRICE_FLAG = 10;   //   'X 市價(1), 限價(0)               *             *               *
        public const int ORDER_ARGS_ODPRICE = 11;         //'9 價格                           *             *               *
        public const int ORDER_ARGS_ODQTY = 12;           //'9 數量                           *             *               *
        public const int ORDER_ARGS_ODKEY = 13;           //'X Order Key                      *             *               *
        public const int ORDER_ARGS_OPENCLOSE = 14;    //   'X -                          新倉(O)/平倉(C)   *               *
        public const int ORDER_ARGS_MTH = 15;             //'X -                              -       (第一腳)履約年月      *
        public const int ORDER_ARGS_CP = 16;              //'X -                              -       (第一腳)Call(C)/Put(P)  *
        public const int ORDER_ARGS_STRIKE = 17;        //  '9 -                              -       (第一腳)履約價          *
        public const int ORDER_ARGS_ID2 = 18;             //'X -                              -             -           (第二腳)代碼
        public const int ORDER_ARGS_BS2 = 19;             //'X -                              -             -           (第二腳)買賣別
        public const int ORDER_ARGS_MTH2 = 20;           // 'X -                              -             -           (第二腳)履約年月
        public const int ORDER_ARGS_CP2 = 21;             //'X -                              -             -           (第二腳)CallPut
        public const int ORDER_ARGS_STRIKE2 = 22;        // '9 -                              -             -           (第二腳)履約價
        public const int ORDER_ARGS_MARKETTYPE = 23;  //    '上市(T)/上櫃(O)                  -             -               -
        // '-表示不使用 *表示同左用法
        public const int ORDER_ARGS_EXCHANGE = 24;
        public const int ORDER_ARGS_STOPPRICE = 25;
        public const int ORDER_ARGS_DAYTRADE = 26;

        //'以下為刪單改量用到的欄位
        public const int ORDER_ARGS_ORGSEQ = 27;     // '原始網路單號
        public const int ORDER_ARGS_ORGSOURCE = 28;   //'原始來源別
        public const int ORDER_ARGS_ORDNO = 29;       //委託書號
        public const int ORDER_ARGS_CANCELQTY = 30;   //'取消股數/口數

        public const int ORDER_ARGS_AFTERQTY = 31;
        public const int ORDER_ARGS_TRANSDATE = 32;    //'交易日
        public const int ORDER_ARGS_MATCHQTY = 33; //'成交口數
        private AxICETRADEAPILib.AxICETRADEAPI axICETRADEAPI1;

        //現貨-----------------------------------------------------------------------
        //'取得分公司號
        public static string m_StkBranch = "";
        //'取得帳號
        public static string m_StkAccount = "";
        //取得帳號名稱
        public static string m_StkName = "";
        //取得營業員
        public static string m_StkAgentId = "";
        //期貨---------------------------------------------------------------------
        //    '取得分公司號
        public static string m_Branch = "";
        //    '取得帳號
        public static string m_Account = "";
        //    '取得帳號名稱
        public static string m_Name = "";
        //    '取得營業員
        public static string m_AgentId = "";

        public class TRptData
        {
            public int nType;
            public int nIndex;
            public int nGridNum;
            public String nOrderNo;
        }

        public class Signal
        {
            public String orderId;
            public String name;
            public int? type;
            public String action;
            public String category;
            public int? quantity;
            public int? direction;
            public String state;
            public float? price;
            public float? filed_price;
            public String specify_entry;
            public String date;
            public String exit_from;
        }


        ArrayList m_OrderReport = new ArrayList();
        ArrayList m_OBOrderReport = new ArrayList();
        ArrayList m_DealReport = new ArrayList();
        ArrayList m_OBDealReport = new ArrayList();


        int m_OrderRow;
        int m_DealRow;
        int m_OBOrderRow;
        int m_OBDealRow;


        public const int ROC_ID = 34;
        public const int CUST_PWD = 35;
        public const int BRANCH_ID = 1;
        public const int CUST_ID = 39;
        public const int CUST_NAME = 40;
        public const int AGENT_ID = 5;
        public const int ACCOUNT_TYPE = 59;


        public const int ITS_REPORT_LOGIN_OK = 1;
        public const int ITS_REPORT_LOGIN_ERROR = 2;

        public const String ACTION_BUY = "buy";
        public const String ACTION_SELL = "sell";
        public const String ACTION_SELLSHORT = "sellshort";
        public const String ACTION_BUYTOCOVER = "buytocover";

        public const String CATEGORY_MARKET = "market";
        public const String CATEGORY_STOP = "stop";
        public const String CATEGORY_LIMIT = "limit";

        public static readonly Dictionary<String, String> BS_MAP = new Dictionary<String, String>()
        {
            { ACTION_BUY, "B" },
            { ACTION_SELL, "S" },
            { ACTION_SELLSHORT, "S" },
            { ACTION_BUYTOCOVER, "B" }
        };

        public class OrderModel
        {
            public string roc_id { get; set; }
            public string password { get; set; }
            public string branch_id { get; set; }
            public string cust_id { get; set; }
            public string agent_id { get; set; }
            public string id { get; set; }
            public string mth { get; set; }
            public string bs_action { get; set; }
            public string price_flag { get; set; }
            public string price { get; set; }
            public string order_id { get; set; }
            public int order_quantity { get; set; }
            public int order_type { get; set; }
            public string open_close { get; set; }
            public int ca_type { get; set; }

            public bool isChecked { get; set; }
        }

        public static readonly Dictionary<String, String> CATEGORY_MAP = new Dictionary<String, String>()
        {
            { CATEGORY_MARKET, "1" },
            { CATEGORY_LIMIT, "0" }
        };

        public static List<Signal> pendingSignals = new List<Signal>();
        public static List<Signal> stopSignals = new List<Signal>();
        private void NewOrder(OrderModel orderModel)
        {
            //期貨下單
            object[] varData = new object[28];
            varData[ORDER_ARGS_ROCID] = orderModel.roc_id;//user_身分證字號
            varData[ORDER_ARGS_PASSWORD] = orderModel.password;//user_password
            varData[ORDER_ARGS_BRANCHID] = orderModel.branch_id;//分公司代號
            varData[ORDER_ARGS_CUSTID] = orderModel.cust_id;//帳號
            varData[ORDER_ARGS_AGENTID] = orderModel.agent_id;//AE代號
            varData[ORDER_ARGS_SOURCE] = "IC";        //'來源別, IC指艾揚, 可任意填上2碼代碼,代表由何處下單
            varData[ORDER_ARGS_ID] = orderModel.id;//商品代號
            varData[ORDER_ARGS_MTH] = orderModel.mth;//交易月份
            varData[ORDER_ARGS_BS] = BS_MAP[orderModel.bs_action];//BS
            varData[ORDER_ARGS_PRICE_FLAG] = CATEGORY_MAP[orderModel.price_flag];//限市價,市價=1,限價=0
            string ftr_id = varData[ORDER_ARGS_ID].ToString();
            if (ftr_id == "RTF" || ftr_id == "RHF")
                varData[ORDER_ARGS_ODPRICE] = Convert.ToDouble(orderModel.price) * 1000000;        //'委託價格需乘上1000000, 末六位是小數位數
            else
                varData[ORDER_ARGS_ODPRICE] = Convert.ToDouble(orderModel.price) * 1000;        //'委託價格需乘上1000, 末三位是小數位數
            varData[ORDER_ARGS_ODQTY] = Convert.ToInt32(orderModel.order_quantity);
            varData[ORDER_ARGS_ODTYPE] = orderModel.order_type;  //'ROD/IOC/FOK

            varData[ORDER_ARGS_ODKEY] = orderModel.order_id;  //'此筆下單的key, 每次下單必須有一個unique的key
            varData[ORDER_ARGS_OPENCLOSE] = orderModel.open_close;

            object Data = varData;

            if (orderModel.isChecked == false)
                axICETRADEAPI1.NeedCA = false;
            else
                axICETRADEAPI1.NeedCA = true;
            axICETRADEAPI1.CAType = Convert.ToInt32(orderModel.ca_type);
            int tmp = axICETRADEAPI1.PlaceFutOrder2(Data);
            Console.Write(tmp.ToString());
        }

        private void CancelOrder(OrderModel orderModel)
        {
            var dataGridView1 = new DataGridView();
            int nType = -1;
            int nIndex = -1;
            
            if (orderModel.order_id.Trim() != "")
            {
                foreach (DataGridViewRow row in dataGridView1.Rows)
                {
                    if (row.Cells["Column4"].Value.ToString().Trim() == orderModel.order_id.Trim())
                    {
                        nType = Convert.ToInt16(row.Cells["DataType"].Value);
                        nIndex = Convert.ToInt16(row.Cells["DataIndex"].Value);
                        break;
                    }
                }
                if ((nType >= 0) && (nIndex >= 0))
                {
                    object[] varData = new object[34];
                    varData[ORDER_ARGS_ROCID] = orderModel.roc_id;
                    varData[ORDER_ARGS_PASSWORD] = orderModel.password;
                    varData[ORDER_ARGS_BRANCHID] = axICETRADEAPI1.GetReportString(nType, nIndex, BRANCH_ID);
                    varData[ORDER_ARGS_CUSTID] = axICETRADEAPI1.GetReportString(nType, nIndex, CUST_ID);
                    varData[ORDER_ARGS_AGENTID] = m_AgentId;
                    varData[ORDER_ARGS_SOURCE] = "IC";
                    varData[ORDER_ARGS_ODKEY] = orderModel.order_id;  //此筆刪改單的key, 每次下單必須有一個unique的key                                   
                    varData[ORDER_ARGS_ORGSEQ] = axICETRADEAPI1.GetReportString(nType, nIndex, F_OD_SEQ);
                    varData[ORDER_ARGS_ORGSOURCE] = axICETRADEAPI1.GetReportString(nType, nIndex, SRC_CODE);
                    varData[ORDER_ARGS_ORDNO] = axICETRADEAPI1.GetReportString(nType, nIndex, ORDNO);
                    varData[ORDER_ARGS_CANCELQTY] = axICETRADEAPI1.GetReportValue(nType, nIndex, OD_QTY);
                    varData[ORDER_ARGS_ID] = axICETRADEAPI1.GetReportString(nType, nIndex, FTR_ID);
                    varData[ORDER_ARGS_MTH] = axICETRADEAPI1.GetReportString(nType, nIndex, FTR_MTH);
                    varData[ORDER_ARGS_BS] = axICETRADEAPI1.GetReportString(nType, nIndex, BUYSELL);
                    varData[ORDER_ARGS_PRICE_FLAG] = axICETRADEAPI1.GetReportString(nType, nIndex, PRICE_FLAG);
                    varData[ORDER_ARGS_ODPRICE] = axICETRADEAPI1.GetReportValue(nType, nIndex, OD_PRICE);
                    varData[ORDER_ARGS_ODQTY] = axICETRADEAPI1.GetReportValue(nType, nIndex, OD_QTY);
                    varData[ORDER_ARGS_OPENCLOSE] = axICETRADEAPI1.GetReportString(nType, nIndex, OPENCLOSE);
                    varData[ORDER_ARGS_TRANSDATE] = axICETRADEAPI1.GetReportString(nType, nIndex, TRANS_DATE);
                    varData[ORDER_ARGS_CP] = axICETRADEAPI1.GetReportString(nType, nIndex, CALLPUT);
                    varData[ORDER_ARGS_STRIKE] = axICETRADEAPI1.GetReportValue(nType, nIndex, STRIKE_PRICE);
                    varData[ORDER_ARGS_ODTYPE] = axICETRADEAPI1.GetReportString(nType, nIndex, OD_TYPE);

                    String sHeader = axICETRADEAPI1.GetReportString(nType, nIndex, HEADER);

                    if (sHeader == "05")
                    {
                        object Data = varData;
                        int tmp = axICETRADEAPI1.ReduceFutOrder2(0, Data);
                        Console.WriteLine(tmp.ToString());
                    }
                    else
                    {
                        object Data = varData;
                        int tmp = axICETRADEAPI1.ReduceOptOrder2(0, Data);
                        Console.WriteLine(tmp.ToString());
                    }
                }
            }
        }
    }
}
