using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Collections;
using System.Threading;
using StackExchange.Redis;
using Newtonsoft.Json;

namespace IceGlobalTradeAPI
{
    public partial class Form1 : Form
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

        public sealed class RedisConnection
        {
            private static Lazy<RedisConnection> lazy = new Lazy<RedisConnection>(() =>
            {
                if (String.IsNullOrEmpty(_settingOption)) throw new InvalidOperationException("Please call Init() first.");
                return new RedisConnection();
            });

            private static string _settingOption;

            public readonly ConnectionMultiplexer ConnectionMultiplexer;

            public static RedisConnection Instance
            {
                get
                {
                    return lazy.Value;
                }
            }

            private RedisConnection()
            {
                ConnectionMultiplexer = ConnectionMultiplexer.Connect(_settingOption);
            }

            public static void Init(string settingOption)
            {
                _settingOption = settingOption;
            }
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

        public static readonly Dictionary<String, String> CATEGORY_MAP = new Dictionary<String, String>()
        {
            { CATEGORY_MARKET, "1" },
            { CATEGORY_LIMIT, "0" }
        };

        public static List<Signal> pendingSignals = new List<Signal>();
        public static List<Signal> stopSignals = new List<Signal>();

        public Form1()
        {
            InitializeComponent();
        }

        private void ReceiveSignals()
        {
            try
            {
                RedisConnection.Init("localhost:6379");
                var redis = RedisConnection.Instance.ConnectionMultiplexer;
                var db = redis.GetDatabase(0);
                var sub = redis.GetSubscriber();
                sub.Subscribe("signals_from_core", (channel, message) =>
                {
                    // MessageBox.Show($"{DateTime.Now.ToString("yyyy-MM-dd hh:mm:ss.fff")} - Received message {message}");
                    var signals = JsonConvert.DeserializeObject<List<Signal>>(message);
                    if (pendingSignals.Any())
                    {
                        var signalIds = signals.Select(s => s.orderId).ToList();
                        var pendingIds = pendingSignals.Select(s => s.orderId).ToList();

                        // get cancel signals
                        var cancelSingal = new List<Signal>();
                        foreach (var p in pendingSignals)
                        {
                            if (!signalIds.Contains(p.orderId))
                            {
                                cancelSingal.Add(p);
                            }
                        }
                        foreach (var s in cancelSingal)
                        {
                            //MessageBox.Show($"cancel: {s.orderId}");
                            CancelOrder(s);
                        }

                        // get new signals
                        var newSignals = new List<Signal>();
                        foreach (var s in signals)
                        {
                            if (!pendingIds.Contains(s.orderId))
                            {
                                newSignals.Add(s);
                            }
                        }
                        ClassifySignal(newSignals);
                    }
                    else
                    {
                        pendingSignals = signals;
                        ClassifySignal(signals);
                    }
                });
            }
            catch (Exception e)
            {
                MessageBox.Show(e.ToString());
            }
        }

        private void ClassifySignal(List<Signal> signals)
        {
            lock (stopSignals)
            {
                stopSignals.Clear();
                foreach (var s in signals)
                {
                    if (CATEGORY_STOP.Equals(s.category))
                    {
                        stopSignals.Add(s);
                    }
                    else
                    {
                        NewOrder(s);
                    }
                }
            }
        }

        public void StopDetect()
        {
            try
            {
                RedisConnection.Init("localhost:6379");
                var redis = RedisConnection.Instance.ConnectionMultiplexer;
                var db = redis.GetDatabase(0);
                var sub = redis.GetSubscriber();
                sub.Subscribe("realtime_price", (channel, message) =>
                {
                    float lastPrice = (float)message;
                    MessageBox.Show(message);
                    lock (stopSignals)
                    {
                        foreach (var s in stopSignals)
                        {
                            if
                            (
                                (ACTION_BUY.Equals(s.action) && lastPrice >= s.price) ||
                                (ACTION_SELL.Equals(s.action) && lastPrice <= s.price) ||
                                (ACTION_SELLSHORT.Equals(s.action) && lastPrice <= s.price) ||
                                (ACTION_BUYTOCOVER.Equals(s.action) && lastPrice >= s.price)
                            )
                            {
                                s.price = 0;
                                s.category = CATEGORY_MARKET;
                                NewOrder(s);
                            }
                        }
                    }
                });
            }
            catch (Exception e)
            {
                MessageBox.Show(e.ToString());
            }
        }

        private void NewOrder(Signal signal)
        {
            //期貨下單
            object[] varData = new object[28];
            varData[ORDER_ARGS_ROCID] = textBox4.Text;//user_身分證字號
            varData[ORDER_ARGS_PASSWORD] = textBox5.Text;//user_password
            varData[ORDER_ARGS_BRANCHID] = comboBox1.Text;//分公司代號
            varData[ORDER_ARGS_CUSTID] = comboBox2.Text;//帳號
            varData[ORDER_ARGS_AGENTID] = m_AgentId;//AE代號
            varData[ORDER_ARGS_SOURCE] = "IC";        //'來源別, IC指艾揚, 可任意填上2碼代碼,代表由何處下單
            varData[ORDER_ARGS_ID] = textBox6.Text;//商品代號
            varData[ORDER_ARGS_MTH] = textBox15.Text;//交易月份
            varData[ORDER_ARGS_BS] = BS_MAP[signal.action];//BS
            varData[ORDER_ARGS_PRICE_FLAG] = CATEGORY_MAP[signal.category];//限市價,市價=1,限價=0
            string ftr_id = varData[ORDER_ARGS_ID].ToString();
            if (ftr_id == "RTF" || ftr_id == "RHF")
                varData[ORDER_ARGS_ODPRICE] = Convert.ToDouble(signal.price) * 1000000;        //'委託價格需乘上1000000, 末六位是小數位數
            else
                varData[ORDER_ARGS_ODPRICE] = Convert.ToDouble(signal.price) * 1000;        //'委託價格需乘上1000, 末三位是小數位數
            varData[ORDER_ARGS_ODQTY] = Convert.ToInt32(textBox12.Text);
            varData[ORDER_ARGS_ODTYPE] = textBox8.Text;  //'ROD/IOC/FOK

            varData[ORDER_ARGS_ODKEY] = signal.orderId;  //'此筆下單的key, 每次下單必須有一個unique的key
            varData[ORDER_ARGS_OPENCLOSE] = textBox13.Text;

            object Data = varData;

            if (checkBox1.Checked == false)
                axICETRADEAPI1.NeedCA = false;
            else
                axICETRADEAPI1.NeedCA = true;
            axICETRADEAPI1.CAType = Convert.ToInt32(textBox23.Text);

            int tmp = axICETRADEAPI1.PlaceFutOrder2(Data);
            MessageBox.Show(tmp.ToString());
        }

        private void CancelOrder(Signal signal)
        {
            int nType = -1;
            int nIndex = -1;
            if (textBox24.Text.Trim() != "")
            {
                foreach (DataGridViewRow row in dataGridView1.Rows)
                {
                    if (row.Cells["Column4"].Value.ToString().Trim() == textBox24.Text.Trim())
                    {
                        nType = Convert.ToInt16(row.Cells["DataType"].Value);
                        nIndex = Convert.ToInt16(row.Cells["DataIndex"].Value);
                        break;
                    }
                }
                if ((nType >= 0) && (nIndex >= 0))
                {
                    object[] varData = new object[34];
                    varData[ORDER_ARGS_ROCID] = textBox4.Text;
                    varData[ORDER_ARGS_PASSWORD] = textBox5.Text;
                    varData[ORDER_ARGS_BRANCHID] = axICETRADEAPI1.GetReportString(nType, nIndex, BRANCH_ID);
                    varData[ORDER_ARGS_CUSTID] = axICETRADEAPI1.GetReportString(nType, nIndex, CUST_ID);
                    varData[ORDER_ARGS_AGENTID] = m_AgentId;
                    varData[ORDER_ARGS_SOURCE] = "IC";
                    varData[ORDER_ARGS_ODKEY] = textBox14.Text;  //此筆刪改單的key, 每次下單必須有一個unique的key                                   
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
                        MessageBox.Show(tmp.ToString());
                    }
                    else
                    {
                        object Data = varData;
                        int tmp = axICETRADEAPI1.ReduceOptOrder2(0, Data);
                        MessageBox.Show(tmp.ToString());
                    }
                }
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            int rtn;
            axICETRADEAPI1.CAPath = textBox25.Text;
            axICETRADEAPI1.CAPassword = textBox26.Text;
            rtn = axICETRADEAPI1.Login(1, textBox1.Text, textBox2.Text, Convert.ToInt32(textBox3.Text), "", 0, "ICE", "iRealII", textBox4.Text, "", "", textBox5.Text, Convert.ToInt32(textBox22.Text));
            //            MessageBox.Show(rtn.ToString());
            Thread t1 = new Thread(ReceiveSignals);
            t1.IsBackground = true;
            t1.Start();

            Thread t2 = new Thread(StopDetect);
            t2.IsBackground = true;
            t2.Start();
        }

        private void button4_Click(object sender, EventArgs e)
        {
            //期貨下單

            object[] varData = new object[28];
            varData[ORDER_ARGS_ROCID] = textBox4.Text;//user_身分證字號
            varData[ORDER_ARGS_PASSWORD] = textBox5.Text;//user_password
            varData[ORDER_ARGS_BRANCHID] = comboBox1.Text;//分公司代號
            varData[ORDER_ARGS_CUSTID] = comboBox2.Text;//帳號
            varData[ORDER_ARGS_AGENTID] = m_AgentId;//AE代號
            varData[ORDER_ARGS_SOURCE] = "IC";        //'來源別, IC指艾揚, 可任意填上2碼代碼,代表由何處下單
            varData[ORDER_ARGS_ID] = textBox6.Text;//商品代號
            varData[ORDER_ARGS_MTH] = textBox15.Text;//交易月份
            varData[ORDER_ARGS_BS] = textBox7.Text;//BS
            varData[ORDER_ARGS_PRICE_FLAG] = textBox10.Text;//限市價,市價=1,限價=0
            string ftr_id = varData[ORDER_ARGS_ID].ToString();
            if (ftr_id == "RTF" || ftr_id == "RHF")
                varData[ORDER_ARGS_ODPRICE] = Convert.ToDouble(textBox11.Text) * 1000000;        //'委託價格需乘上1000000, 末六位是小數位數
            else
                varData[ORDER_ARGS_ODPRICE] = Convert.ToDouble(textBox11.Text) * 1000;        //'委託價格需乘上1000, 末三位是小數位數
            varData[ORDER_ARGS_ODQTY] = Convert.ToInt32(textBox12.Text);
            varData[ORDER_ARGS_ODTYPE] = textBox8.Text;  //'ROD/IOC/FOK

            varData[ORDER_ARGS_ODKEY] = textBox14.Text;  //'此筆下單的key, 每次下單必須有一個unique的key
            varData[ORDER_ARGS_OPENCLOSE] = textBox13.Text;

            object Data = varData;

            if (checkBox1.Checked == false)
                axICETRADEAPI1.NeedCA = false;
            else
                axICETRADEAPI1.NeedCA = true;
            axICETRADEAPI1.CAType = Convert.ToInt32(textBox23.Text);

            int tmp = axICETRADEAPI1.PlaceFutOrder2(Data);
            MessageBox.Show(tmp.ToString());
        }

        private void button3_Click(object sender, EventArgs e)
        {
            //證券下單
            object[] varData = new object[24];
            varData[ORDER_ARGS_ROCID] = textBox4.Text;//user_身分證字號
            varData[ORDER_ARGS_PASSWORD] = textBox5.Text;//user_password
            varData[ORDER_ARGS_BRANCHID] = comboBox1.Text;//分公司代號
            varData[ORDER_ARGS_CUSTID] = comboBox2.Text;//帳號
            varData[ORDER_ARGS_AGENTID] = m_AgentId;//AE代號
            varData[ORDER_ARGS_SOURCE] = "IC";        //'來源別, IC指艾揚, 可任意填上2碼代碼,代表由何處下單
            varData[ORDER_ARGS_ID] = textBox6.Text;//商品代號
            varData[ORDER_ARGS_BS] = textBox7.Text;//BS
            varData[ORDER_ARGS_PRICE_FLAG] = textBox10.Text;//限市價,市價=1,限價=0
            varData[ORDER_ARGS_ODPRICE] = Convert.ToDouble(textBox11.Text) * 1000;        //'委託價格需乘上1000, 末三位是小數位數
            varData[ORDER_ARGS_ODQTY] = Convert.ToInt32(textBox12.Text);
            varData[ORDER_ARGS_ODTYPE] = textBox8.Text;  //0現股/1融資/2融券
            varData[ORDER_ARGS_TRADE_TYPE] = textBox9.Text;   //N/O/F
            varData[ORDER_ARGS_ODKEY] = textBox14.Text;  //'此筆下單的key, 每次下單必須有一個unique的key
            varData[ORDER_ARGS_MARKETTYPE] = textBox18.Text;//T/O;
            object Data = varData;

            if (checkBox1.Checked == false)
                axICETRADEAPI1.NeedCA = false;
            else
                axICETRADEAPI1.NeedCA = true;

            axICETRADEAPI1.CAType = Convert.ToInt32(textBox23.Text);

            int tmp = axICETRADEAPI1.PlaceStkOrder2(Data);
            MessageBox.Show(tmp.ToString());
        }

        private void button2_Click(object sender, EventArgs e)
        {
            axICETRADEAPI1.Logout();
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void button6_Click(object sender, EventArgs e)
        {
            //國外期貨下單
            object[] varData = new object[28];
            varData[ORDER_ARGS_ROCID] = textBox4.Text;//user_身分證字號
            varData[ORDER_ARGS_PASSWORD] = textBox5.Text;//user_password
            varData[ORDER_ARGS_BRANCHID] = comboBox1.Text;//分公司代號
            varData[ORDER_ARGS_CUSTID] = comboBox2.Text;//帳號
            varData[ORDER_ARGS_AGENTID] = m_AgentId;//AE代號
            varData[ORDER_ARGS_SOURCE] = "IC";        //'來源別, IC指艾揚, 可任意填上2碼代碼,代表由何處下單
            varData[ORDER_ARGS_EXCHANGE] = textBox19.Text; //國外交易所
            varData[ORDER_ARGS_ID] = textBox6.Text;//商品代號
            varData[ORDER_ARGS_MTH] = textBox15.Text;//交易月份
            varData[ORDER_ARGS_BS] = textBox7.Text;//BS
            varData[ORDER_ARGS_PRICE_FLAG] = textBox10.Text;//限市價,市價=1,限價=0
            varData[ORDER_ARGS_ODPRICE] = (Convert.ToDouble(textBox11.Text) * 1000000).ToString();        //'委託價格需乘上1000, 末三位是小數位數
            varData[ORDER_ARGS_ODQTY] = Convert.ToInt32(textBox12.Text);
            varData[ORDER_ARGS_ODTYPE] = textBox8.Text;  //'ROD/IOC/FOK

            varData[ORDER_ARGS_ODKEY] = textBox14.Text;  //'此筆下單的key, 每次下單必須有一個unique的key
            varData[ORDER_ARGS_OPENCLOSE] = textBox13.Text;
            varData[ORDER_ARGS_STOPPRICE] = (Convert.ToDouble(textBox20.Text) * 1000000).ToString();
            varData[ORDER_ARGS_DAYTRADE] = textBox21.Text;
            object Data = varData;

            if (checkBox1.Checked == false)
                axICETRADEAPI1.NeedCA = false;
            else
                axICETRADEAPI1.NeedCA = true;

            axICETRADEAPI1.CAType = Convert.ToInt32(textBox23.Text);

            int tmp = axICETRADEAPI1.PlaceOBFutOrder2(Data);
            MessageBox.Show(tmp.ToString());
        }

        private void button5_Click(object sender, EventArgs e)
        {

            //選擇權下單
            object[] varData = new object[28];
            varData[ORDER_ARGS_ROCID] = textBox4.Text;//user_身分證字號
            varData[ORDER_ARGS_PASSWORD] = textBox5.Text;//user_password
            varData[ORDER_ARGS_BRANCHID] = comboBox1.Text;//分公司代號
            varData[ORDER_ARGS_CUSTID] = comboBox2.Text;//帳號
            varData[ORDER_ARGS_AGENTID] = m_AgentId;//AE代號
            varData[ORDER_ARGS_SOURCE] = "IC";        //'來源別, IC指艾揚, 可任意填上2碼代碼,代表由何處下單
            varData[ORDER_ARGS_ID] = textBox6.Text;//商品代號
            varData[ORDER_ARGS_CP] = textBox16.Text;//CAll/PUT
            varData[ORDER_ARGS_STRIKE] = Convert.ToDouble(textBox17.Text) * 1000;
            varData[ORDER_ARGS_MTH] = textBox15.Text;//交易月份
            varData[ORDER_ARGS_BS] = textBox7.Text;//BS
            varData[ORDER_ARGS_PRICE_FLAG] = textBox10.Text;//限市價,市價=1,限價=0
            varData[ORDER_ARGS_ODPRICE] = Convert.ToDouble(textBox11.Text) * 1000;        //'委託價格需乘上1000, 末三位是小數位數
            varData[ORDER_ARGS_ODQTY] = Convert.ToInt32(textBox12.Text);
            varData[ORDER_ARGS_ODTYPE] = textBox8.Text;  //'ROD/IOC/FOK

            varData[ORDER_ARGS_ODKEY] = textBox14.Text;  //'此筆下單的key, 每次下單必須有一個unique的key
            varData[ORDER_ARGS_OPENCLOSE] = textBox13.Text;

            object Data = varData;
            if (checkBox1.Checked == false)
                axICETRADEAPI1.NeedCA = false;
            else
                axICETRADEAPI1.NeedCA = true;
            axICETRADEAPI1.CAType = Convert.ToInt32(textBox23.Text);

            int tmp = axICETRADEAPI1.PlaceOptOrder2(Data);
            MessageBox.Show(tmp.ToString());
        }

        private void button7_Click(object sender, EventArgs e)
        {
            //刪單
            int nType = -1;
            int nIndex = -1;
            if (textBox24.Text.Trim() != "")
            {
                foreach (DataGridViewRow row in dataGridView1.Rows)
                {
                    if (row.Cells["Column4"].Value.ToString().Trim() == textBox24.Text.Trim())
                    {
                        nType = Convert.ToInt16(row.Cells["DataType"].Value);
                        nIndex = Convert.ToInt16(row.Cells["DataIndex"].Value);
                        break;
                    }
                }
                if ((nType >= 0) && (nIndex >= 0))
                {
                    object[] varData = new object[34];
                    varData[ORDER_ARGS_ROCID] = textBox4.Text;
                    varData[ORDER_ARGS_PASSWORD] = textBox5.Text;
                    varData[ORDER_ARGS_BRANCHID] = axICETRADEAPI1.GetReportString(nType, nIndex, BRANCH_ID);
                    varData[ORDER_ARGS_CUSTID] = axICETRADEAPI1.GetReportString(nType, nIndex, CUST_ID);
                    varData[ORDER_ARGS_AGENTID] = m_AgentId;
                    varData[ORDER_ARGS_SOURCE] = "IC";
                    varData[ORDER_ARGS_ODKEY] = textBox14.Text;  //此筆刪改單的key, 每次下單必須有一個unique的key                                   
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
                        MessageBox.Show(tmp.ToString());
                    }
                    else
                    {
                        object Data = varData;
                        int tmp = axICETRADEAPI1.ReduceOptOrder2(0, Data);
                        MessageBox.Show(tmp.ToString());
                    }
                }
            }
        }

        private void axICETRADEAPI1_ChgDealReport(object sender, AxICETRADEAPILib._DICETRADEAPIEvents_ChgDealReportEvent e)
        {
            int Row;
            foreach (TRptData tmpRptData in m_DealReport)
            {
                if ((tmpRptData.nIndex == e.nDataIndex) && (tmpRptData.nType == e.nDataType))
                {
                    string ftr_id = axICETRADEAPI1.GetReportString(e.nDataType, e.nDataIndex, FTR_ID);
                    Row = tmpRptData.nGridNum;
                    dataGridView2.Rows[Row].Cells[0].Value = axICETRADEAPI1.GetReportString(e.nDataType, e.nDataIndex, FTR_ID);
                    dataGridView2.Rows[Row].Cells[1].Value = axICETRADEAPI1.GetReportString(e.nDataType, e.nDataIndex, FTR_MTH);
                    dataGridView2.Rows[Row].Cells[2].Value = axICETRADEAPI1.GetReportString(e.nDataType, e.nDataIndex, CALLPUT);
                    dataGridView2.Rows[Row].Cells[3].Value = axICETRADEAPI1.GetReportValue(e.nDataType, e.nDataIndex, STRIKE_PRICE) / 1000;
                    dataGridView2.Rows[Row].Cells[4].Value = axICETRADEAPI1.GetReportString(e.nDataType, e.nDataIndex, ORDNO);
                    dataGridView2.Rows[Row].Cells[5].Value = axICETRADEAPI1.GetReportString(e.nDataType, e.nDataIndex, BUYSELL);
                    if (ftr_id == "RTF" || ftr_id == "RHF")
                        dataGridView2.Rows[Row].Cells[6].Value = (double)axICETRADEAPI1.GetReportValue(e.nDataType, e.nDataIndex, OD_PRICE) / 1000000;
                    else
                        dataGridView2.Rows[Row].Cells[6].Value = (double)axICETRADEAPI1.GetReportValue(e.nDataType, e.nDataIndex, OD_PRICE) / 1000;
                    dataGridView2.Rows[Row].Cells[7].Value = axICETRADEAPI1.GetReportValue(e.nDataType, e.nDataIndex, DEAL_QTY);
                    break;
                }
            }
        }

        private void axICETRADEAPI1_ChgOrderReport(object sender, AxICETRADEAPILib._DICETRADEAPIEvents_ChgOrderReportEvent e)
        {
            int Row;
            foreach (TRptData tmpRptData in m_OrderReport)
            {
                if ((tmpRptData.nIndex == e.nDataIndex) && (tmpRptData.nType == e.nDataType))
                {
                    string ftr_id = axICETRADEAPI1.GetReportString(e.nDataType, e.nDataIndex, FTR_ID);
                    int formtype = axICETRADEAPI1.GetReportValue(e.nDataType, e.nDataIndex, FORM_TYPE);
                    string header = axICETRADEAPI1.GetReportString(e.nDataType, e.nDataIndex, HEADER);
                    string ordno = axICETRADEAPI1.GetReportString(e.nDataType, e.nDataIndex, ORDNO);

                    Row = tmpRptData.nGridNum;
                    dataGridView1.Rows[Row].Cells[0].Value = axICETRADEAPI1.GetReportString(e.nDataType, e.nDataIndex, FTR_ID);
                    dataGridView1.Rows[Row].Cells[1].Value = axICETRADEAPI1.GetReportString(e.nDataType, e.nDataIndex, FTR_MTH);
                    dataGridView1.Rows[Row].Cells[2].Value = axICETRADEAPI1.GetReportString(e.nDataType, e.nDataIndex, CALLPUT);
                    dataGridView1.Rows[Row].Cells[3].Value = axICETRADEAPI1.GetReportValue(e.nDataType, e.nDataIndex, STRIKE_PRICE) / 1000;
                    dataGridView1.Rows[Row].Cells[4].Value = axICETRADEAPI1.GetReportString(e.nDataType, e.nDataIndex, ORDNO);
                    dataGridView1.Rows[Row].Cells[5].Value = axICETRADEAPI1.GetReportString(e.nDataType, e.nDataIndex, BUYSELL);
                    if (ftr_id == "RTF" || ftr_id == "RHF")
                        dataGridView1.Rows[Row].Cells[6].Value = (double)axICETRADEAPI1.GetReportValue(e.nDataType, e.nDataIndex, OD_PRICE) / 1000000;
                    else
                        dataGridView1.Rows[Row].Cells[6].Value = (double)axICETRADEAPI1.GetReportValue(e.nDataType, e.nDataIndex, OD_PRICE) / 1000;
                    dataGridView1.Rows[Row].Cells[7].Value = axICETRADEAPI1.GetReportValue(e.nDataType, e.nDataIndex, OD_QTY);
                    dataGridView1.Rows[Row].Cells[8].Value = axICETRADEAPI1.GetReportString(e.nDataType, e.nDataIndex, OD_KEY);
                    dataGridView1.Rows[Row].Cells[9].Value = axICETRADEAPI1.GetReportString(e.nDataType, e.nDataIndex, ERR_CODE);
                    dataGridView1.Rows[Row].Cells[10].Value = axICETRADEAPI1.GetReportString(e.nDataType, e.nDataIndex, ERR_MSG);
                    break;
                }
            }
        }

        private void axICETRADEAPI1_ConnectStatusChanged(object sender, AxICETRADEAPILib._DICETRADEAPIEvents_ConnectStatusChangedEvent e)
        {
            string nStatus = e.nStatus.ToString().Trim();
            string tmp = "";
            if (nStatus == "0")
            {
                richTextBox1.AppendText("離線\n");
            }
            else if (nStatus == "1")
            {
                richTextBox1.AppendText("連線中\n");
            }
            else//
            {
                richTextBox1.AppendText("連線成功\n");
                //'連線完成, 跟API取得帳號                                
                axICETRADEAPI1.OrdSubPrefix = "OrdTW";
                axICETRADEAPI1.OBOrdSubPrefix = "OrdOB";

                m_OrderRow = 0;
                m_DealRow = 0;
                m_OBOrderRow = 0;
                m_OBDealRow = 0;

                for (int i = 0; i < axICETRADEAPI1.GetDataCount(ITS_REPORT_LOGIN_OK); i++)
                {
                    //'取得帳號type, S:證券帳號   F:期權帳號
                    tmp = axICETRADEAPI1.GetString(1, i, ACCOUNT_TYPE);
                    if (tmp == "S") //現貨
                    {
                        //'登入取帳號時, 有以下欄位資料可取得
                        //'取得分公司號
                        m_StkBranch = axICETRADEAPI1.GetString(ITS_REPORT_LOGIN_OK, i, BRANCH_ID);
                        //'取得帳號
                        m_StkAccount = axICETRADEAPI1.GetString(ITS_REPORT_LOGIN_OK, i, CUST_ID);
                        //'取得帳號名稱
                        m_StkName = axICETRADEAPI1.GetString(ITS_REPORT_LOGIN_OK, i, CUST_NAME);
                        //'取得營業員
                        m_StkAgentId = axICETRADEAPI1.GetString(ITS_REPORT_LOGIN_OK, i, AGENT_ID);
                        richTextBox1.AppendText("分公司代號=" + m_StkBranch + "\n" + "股票帳號=" + m_StkAccount + "\n" + "帳號名稱=" + m_StkName + "\n" + "營業員=" + m_StkAgentId + "\n");
                        //'MsgBox "STK Account : " + m_StkBranch + "-" + m_StkAccount
                        //'帳號取得後, 跟STFY_API要求訂閱回補委回成回資料
                        if (checkBox2.Checked == false)
                            axICETRADEAPI1.SubscribeByAccount(12, m_Branch, m_Account);
                        axICETRADEAPI1.SubscribeByAccount(0, m_StkBranch, m_StkAccount);
                    }
                    else//期貨
                    {
                        //    '登入取帳號時, 有以下欄位資料可取得
                        //    '取得分公司號
                        m_Branch = axICETRADEAPI1.GetString(ITS_REPORT_LOGIN_OK, i, BRANCH_ID);
                        //    '取得帳號
                        m_Account = axICETRADEAPI1.GetString(ITS_REPORT_LOGIN_OK, i, CUST_ID);
                        //    '取得帳號名稱
                        m_Name = axICETRADEAPI1.GetString(ITS_REPORT_LOGIN_OK, i, CUST_NAME);
                        //    '取得營業員
                        m_AgentId = axICETRADEAPI1.GetString(ITS_REPORT_LOGIN_OK, i, AGENT_ID);
                        richTextBox1.AppendText("分公司代號=" + m_Branch + "\n" + "期貨帳號=" + m_Account + "\n" + "帳號名稱=" + m_Name + "\n" + "營業員=" + m_AgentId + "\n");
                        //    'MsgBox "FUT Account : " + m_Branch + "-" + m_Account
                        //    '帳號取得後, 要求訂閱回補委回成回資料
                        if (checkBox2.Checked == false)
                            axICETRADEAPI1.SubscribeByAccount(12, m_Branch, m_Account);
                        axICETRADEAPI1.SubscribeByAccount(0, m_Branch, m_Account);
                        axICETRADEAPI1.SubscribeByAccount(1, m_Branch, m_Account);

                        comboBox1.Items.Add(m_Branch);
                        comboBox1.SelectedIndex = 0;
                        comboBox2.Items.Add(m_Account);
                        comboBox2.SelectedIndex = 0;
                    }
                }
            }
        }

        private void axICETRADEAPI1_NewDealReport(object sender, AxICETRADEAPILib._DICETRADEAPIEvents_NewDealReportEvent e)
        {
            TRptData tmpRptData = new TRptData();
            tmpRptData.nIndex = e.nDataIndex;
            tmpRptData.nType = e.nDataType;
            tmpRptData.nGridNum = m_DealRow;
            string ftr_id = axICETRADEAPI1.GetReportString(e.nDataType, e.nDataIndex, FTR_ID);

            dataGridView2.Rows.Add();
            dataGridView2.Rows[m_DealRow].Cells[0].Value = axICETRADEAPI1.GetReportString(e.nDataType, e.nDataIndex, FTR_ID);
            dataGridView2.Rows[m_DealRow].Cells[1].Value = axICETRADEAPI1.GetReportString(e.nDataType, e.nDataIndex, FTR_MTH);
            dataGridView2.Rows[m_DealRow].Cells[2].Value = axICETRADEAPI1.GetReportString(e.nDataType, e.nDataIndex, CALLPUT);
            dataGridView2.Rows[m_DealRow].Cells[3].Value = axICETRADEAPI1.GetReportValue(e.nDataType, e.nDataIndex, STRIKE_PRICE) / 1000;
            dataGridView2.Rows[m_DealRow].Cells[4].Value = axICETRADEAPI1.GetReportString(e.nDataType, e.nDataIndex, ORDNO);
            dataGridView2.Rows[m_DealRow].Cells[5].Value = axICETRADEAPI1.GetReportString(e.nDataType, e.nDataIndex, BUYSELL);
            if (ftr_id == "RTF" || ftr_id == "RHF")
                dataGridView2.Rows[m_DealRow].Cells[6].Value = (double)axICETRADEAPI1.GetReportValue(e.nDataType, e.nDataIndex, OD_PRICE) / 1000000;
            else
                dataGridView2.Rows[m_DealRow].Cells[6].Value = (double)axICETRADEAPI1.GetReportValue(e.nDataType, e.nDataIndex, OD_PRICE) / 1000;
            dataGridView2.Rows[m_DealRow].Cells[7].Value = axICETRADEAPI1.GetReportValue(e.nDataType, e.nDataIndex, DEAL_QTY);
            m_DealReport.Add(tmpRptData);
            m_DealRow = m_DealRow + 1;
        }

        private void axICETRADEAPI1_NewOrderReport(object sender, AxICETRADEAPILib._DICETRADEAPIEvents_NewOrderReportEvent e)
        {
            TRptData tmpRptData = new TRptData();
            tmpRptData.nIndex = e.nDataIndex;
            tmpRptData.nType = e.nDataType;
            tmpRptData.nGridNum = m_OrderRow;
            string ftr_id = axICETRADEAPI1.GetReportString(e.nDataType, e.nDataIndex, FTR_ID);

            dataGridView1.Rows.Add();
            dataGridView1.Rows[m_OrderRow].Cells[0].Value = axICETRADEAPI1.GetReportString(e.nDataType, e.nDataIndex, FTR_ID);
            dataGridView1.Rows[m_OrderRow].Cells[1].Value = axICETRADEAPI1.GetReportString(e.nDataType, e.nDataIndex, FTR_MTH);
            dataGridView1.Rows[m_OrderRow].Cells[2].Value = axICETRADEAPI1.GetReportString(e.nDataType, e.nDataIndex, CALLPUT);
            dataGridView1.Rows[m_OrderRow].Cells[3].Value = axICETRADEAPI1.GetReportValue(e.nDataType, e.nDataIndex, STRIKE_PRICE) / 1000;
            dataGridView1.Rows[m_OrderRow].Cells[4].Value = axICETRADEAPI1.GetReportString(e.nDataType, e.nDataIndex, ORDNO);
            tmpRptData.nOrderNo = axICETRADEAPI1.GetReportString(e.nDataType, e.nDataIndex, ORDNO);
            dataGridView1.Rows[m_OrderRow].Cells[5].Value = axICETRADEAPI1.GetReportString(e.nDataType, e.nDataIndex, BUYSELL);
            if (ftr_id == "RTF" || ftr_id == "RHF")
                dataGridView1.Rows[m_OrderRow].Cells[6].Value = (double)axICETRADEAPI1.GetReportValue(e.nDataType, e.nDataIndex, OD_PRICE) / 1000000;
            else
                dataGridView1.Rows[m_OrderRow].Cells[6].Value = (double)axICETRADEAPI1.GetReportValue(e.nDataType, e.nDataIndex, OD_PRICE) / 1000;
            dataGridView1.Rows[m_OrderRow].Cells[7].Value = axICETRADEAPI1.GetReportValue(e.nDataType, e.nDataIndex, OD_QTY);
            dataGridView1.Rows[m_OrderRow].Cells[8].Value = axICETRADEAPI1.GetReportString(e.nDataType, e.nDataIndex, OD_KEY);
            dataGridView1.Rows[m_OrderRow].Cells[9].Value = axICETRADEAPI1.GetReportString(e.nDataType, e.nDataIndex, ERR_CODE);
            dataGridView1.Rows[m_OrderRow].Cells[10].Value = axICETRADEAPI1.GetReportString(e.nDataType, e.nDataIndex, ERR_MSG);
            dataGridView1.Rows[m_OrderRow].Cells[11].Value = e.nDataType;
            dataGridView1.Rows[m_OrderRow].Cells[12].Value = e.nDataIndex;
            m_OrderReport.Add(tmpRptData);
            m_OrderRow = m_OrderRow + 1;
        }

        private void axICETRADEAPI1_OBChgDealReport(object sender, AxICETRADEAPILib._DICETRADEAPIEvents_OBChgDealReportEvent e)
        {
            int Row;
            foreach (TRptData tmpRptData in m_OBDealReport)
            {
                if ((tmpRptData.nIndex == e.nDataIndex) && (tmpRptData.nType == e.nDataType))
                {
                    Row = tmpRptData.nGridNum;
                    dataGridView4.Rows[Row].Cells[0].Value = axICETRADEAPI1.GetOBReportString(e.nDataType, e.nDataIndex, FTR_ID);
                    dataGridView4.Rows[Row].Cells[1].Value = axICETRADEAPI1.GetOBReportString(e.nDataType, e.nDataIndex, FTR_MTH);
                    dataGridView4.Rows[Row].Cells[2].Value = axICETRADEAPI1.GetOBReportString(e.nDataType, e.nDataIndex, CALLPUT);
                    dataGridView4.Rows[Row].Cells[3].Value = axICETRADEAPI1.GetOBReportValue(e.nDataType, e.nDataIndex, STRIKE_PRICE) / 1000;
                    dataGridView4.Rows[Row].Cells[4].Value = axICETRADEAPI1.GetOBReportString(e.nDataType, e.nDataIndex, ORDNO);
                    dataGridView4.Rows[Row].Cells[5].Value = axICETRADEAPI1.GetOBReportString(e.nDataType, e.nDataIndex, BUYSELL);
                    dataGridView4.Rows[Row].Cells[6].Value = axICETRADEAPI1.GetOBReportValue(e.nDataType, e.nDataIndex, OBOD_PRICE) / 1000;
                    dataGridView4.Rows[Row].Cells[7].Value = axICETRADEAPI1.GetOBReportString(e.nDataType, e.nDataIndex, DEAL_QTY);
                    break;
                }
            }
        }

        private void axICETRADEAPI1_OBChgOrderReport(object sender, AxICETRADEAPILib._DICETRADEAPIEvents_OBChgOrderReportEvent e)
        {
            int Row;
            richTextBox1.AppendText("chg\n");
            foreach (TRptData tmpRptData in m_OBOrderReport)
            {
                if ((tmpRptData.nIndex == e.nDataIndex) && (tmpRptData.nType == e.nDataType))
                {
                    Row = tmpRptData.nGridNum;
                    dataGridView3.Rows[Row].Cells[0].Value = axICETRADEAPI1.GetOBReportString(e.nDataType, e.nDataIndex, FTR_ID);
                    dataGridView3.Rows[Row].Cells[1].Value = axICETRADEAPI1.GetOBReportString(e.nDataType, e.nDataIndex, FTR_MTH);
                    dataGridView3.Rows[Row].Cells[2].Value = axICETRADEAPI1.GetOBReportString(e.nDataType, e.nDataIndex, CALLPUT);
                    dataGridView3.Rows[Row].Cells[3].Value = axICETRADEAPI1.GetOBReportValue(e.nDataType, e.nDataIndex, STRIKE_PRICE) / 1000;
                    dataGridView3.Rows[Row].Cells[4].Value = axICETRADEAPI1.GetOBReportString(e.nDataType, e.nDataIndex, ORDNO);
                    dataGridView3.Rows[Row].Cells[5].Value = axICETRADEAPI1.GetOBReportString(e.nDataType, e.nDataIndex, BUYSELL);
                    dataGridView3.Rows[Row].Cells[6].Value = axICETRADEAPI1.GetOBReportValue(e.nDataType, e.nDataIndex, OD_PRICE) / 1000;
                    dataGridView3.Rows[Row].Cells[7].Value = axICETRADEAPI1.GetOBReportValue(e.nDataType, e.nDataIndex, OD_QTY);
                    dataGridView3.Rows[Row].Cells[8].Value = axICETRADEAPI1.GetOBReportString(e.nDataType, e.nDataIndex, OD_KEY);
                    dataGridView3.Rows[Row].Cells[9].Value = axICETRADEAPI1.GetOBReportString(e.nDataType, e.nDataIndex, ERR_CODE);
                    dataGridView3.Rows[Row].Cells[10].Value = axICETRADEAPI1.GetOBReportString(e.nDataType, e.nDataIndex, ERR_MSG);
                    dataGridView3.Rows[Row].Cells[11].Value = axICETRADEAPI1.GetOBReportValue(e.nDataType, e.nDataIndex, FORM_TYPE);
                    break;
                }
            }
        }

        private void axICETRADEAPI1_OBNewDealReport(object sender, AxICETRADEAPILib._DICETRADEAPIEvents_OBNewDealReportEvent e)
        {
            TRptData tmpRptData = new TRptData();
            tmpRptData.nIndex = e.nDataIndex;
            tmpRptData.nType = e.nDataType;
            tmpRptData.nGridNum = m_OBDealRow;
            dataGridView4.Rows.Add();
            dataGridView4.Rows[m_OBDealRow].Cells[0].Value = axICETRADEAPI1.GetOBReportString(e.nDataType, e.nDataIndex, FTR_ID);
            dataGridView4.Rows[m_OBDealRow].Cells[1].Value = axICETRADEAPI1.GetOBReportString(e.nDataType, e.nDataIndex, FTR_MTH);
            dataGridView4.Rows[m_OBDealRow].Cells[2].Value = axICETRADEAPI1.GetOBReportString(e.nDataType, e.nDataIndex, CALLPUT);
            dataGridView4.Rows[m_OBDealRow].Cells[3].Value = axICETRADEAPI1.GetOBReportValue(e.nDataType, e.nDataIndex, STRIKE_PRICE) / 1000;
            dataGridView4.Rows[m_OBDealRow].Cells[4].Value = axICETRADEAPI1.GetOBReportString(e.nDataType, e.nDataIndex, ORDNO);
            dataGridView4.Rows[m_OBDealRow].Cells[5].Value = axICETRADEAPI1.GetOBReportString(e.nDataType, e.nDataIndex, BUYSELL);
            dataGridView4.Rows[m_OBDealRow].Cells[6].Value = axICETRADEAPI1.GetOBReportValue(e.nDataType, e.nDataIndex, OBOD_PRICE) / 1000;
            dataGridView4.Rows[m_OBDealRow].Cells[7].Value = axICETRADEAPI1.GetOBReportValue(e.nDataType, e.nDataIndex, DEAL_QTY);
            m_OBDealReport.Add(tmpRptData);
            m_OBDealRow = m_OBDealRow + 1;
        }

        private void axICETRADEAPI1_OBNewOrderReport(object sender, AxICETRADEAPILib._DICETRADEAPIEvents_OBNewOrderReportEvent e)
        {
            TRptData tmpRptData = new TRptData();
            tmpRptData.nIndex = e.nDataIndex;
            tmpRptData.nType = e.nDataType;
            tmpRptData.nGridNum = m_OBOrderRow;
            richTextBox1.AppendText("new\n");
            dataGridView3.Rows.Add();
            dataGridView3.Rows[m_OBOrderRow].Cells[0].Value = axICETRADEAPI1.GetOBReportString(e.nDataType, e.nDataIndex, FTR_ID);
            dataGridView3.Rows[m_OBOrderRow].Cells[1].Value = axICETRADEAPI1.GetOBReportString(e.nDataType, e.nDataIndex, FTR_MTH);
            dataGridView3.Rows[m_OBOrderRow].Cells[2].Value = axICETRADEAPI1.GetOBReportString(e.nDataType, e.nDataIndex, CALLPUT);
            dataGridView3.Rows[m_OBOrderRow].Cells[3].Value = axICETRADEAPI1.GetOBReportValue(e.nDataType, e.nDataIndex, STRIKE_PRICE) / 1000;
            dataGridView3.Rows[m_OBOrderRow].Cells[4].Value = axICETRADEAPI1.GetOBReportString(e.nDataType, e.nDataIndex, ORDNO);
            tmpRptData.nOrderNo = axICETRADEAPI1.GetOBReportString(e.nDataType, e.nDataIndex, ORDNO);
            dataGridView3.Rows[m_OBOrderRow].Cells[5].Value = axICETRADEAPI1.GetOBReportString(e.nDataType, e.nDataIndex, BUYSELL);
            dataGridView3.Rows[m_OBOrderRow].Cells[6].Value = axICETRADEAPI1.GetOBReportValue(e.nDataType, e.nDataIndex, OD_PRICE) / 1000;
            dataGridView3.Rows[m_OBOrderRow].Cells[7].Value = axICETRADEAPI1.GetOBReportValue(e.nDataType, e.nDataIndex, OD_QTY);
            dataGridView3.Rows[m_OBOrderRow].Cells[8].Value = axICETRADEAPI1.GetOBReportString(e.nDataType, e.nDataIndex, OD_KEY);
            dataGridView3.Rows[m_OBOrderRow].Cells[9].Value = axICETRADEAPI1.GetOBReportString(e.nDataType, e.nDataIndex, ERR_CODE);
            dataGridView3.Rows[m_OBOrderRow].Cells[10].Value = axICETRADEAPI1.GetOBReportString(e.nDataType, e.nDataIndex, ERR_MSG);
            dataGridView3.Rows[m_OBOrderRow].Cells[11].Value = axICETRADEAPI1.GetOBReportValue(e.nDataType, e.nDataIndex, FORM_TYPE);
            dataGridView3.Rows[m_OBOrderRow].Cells[12].Value = e.nDataType;
            dataGridView3.Rows[m_OBOrderRow].Cells[13].Value = e.nDataIndex;

            m_OBOrderReport.Add(tmpRptData);
            m_OBOrderRow = m_OBOrderRow + 1;
        }

        private void axICETRADEAPI1_OBOrdRestoreComplete(object sender, EventArgs e)
        {
            //richTextBox1.AppendText("OB RestoreComplete Trigger\n");
        }

        private void axICETRADEAPI1_OnError(object sender, AxICETRADEAPILib._DICETRADEAPIEvents_OnErrorEvent e)
        {
            //richTextBox1.AppendText(e.errCode.ToString() + ":" + e.errMsg + '\n');
        }

        private void axICETRADEAPI1_OrdRestoreComplete(object sender, EventArgs e)
        {
            richTextBox1.AppendText("RestoreComplete Trigger\n");
        }

        private void button8_Click(object sender, EventArgs e)
        {
            //國外刪單
            int nType = -1;
            int nIndex = -1;
            if (textBox24.Text.Trim() != "")
            {
                foreach (DataGridViewRow row in dataGridView3.Rows)
                {
                    if (row.Cells[4].Value.ToString().Trim() == textBox24.Text.Trim())
                    {
                        nType = Convert.ToInt16(row.Cells[12].Value);
                        nIndex = Convert.ToInt16(row.Cells[13].Value);
                        break;
                    }
                }
                if ((nType >= 0) && (nIndex >= 0))
                {
                    object[] varData = new object[34];
                    varData[ORDER_ARGS_ROCID] = textBox4.Text;
                    varData[ORDER_ARGS_PASSWORD] = textBox5.Text;
                    varData[ORDER_ARGS_ORGSEQ] = axICETRADEAPI1.GetOBReportString(nType, nIndex, F_OD_SEQ);//OrgSeq原始網路單號
                    varData[ORDER_ARGS_BRANCHID] = axICETRADEAPI1.GetOBReportString(nType, nIndex, BRANCH_ID);
                    varData[ORDER_ARGS_CUSTID] = axICETRADEAPI1.GetOBReportString(nType, nIndex, CUST_ID);
                    varData[ORDER_ARGS_SOURCE] = "IC";
                    varData[ORDER_ARGS_ORGSOURCE] = axICETRADEAPI1.GetOBReportString(nType, nIndex, SRC_CODE);//
                    varData[ORDER_ARGS_AGENTID] = m_AgentId;
                    varData[ORDER_ARGS_ORDNO] = axICETRADEAPI1.GetOBReportString(nType, nIndex, ORDNO);

                    varData[ORDER_ARGS_CANCELQTY] = (int)axICETRADEAPI1.GetOBReportValue(nType, nIndex, OD_QTY);
                    varData[ORDER_ARGS_AFTERQTY] = 0;//刪單

                    double dODprice = axICETRADEAPI1.GetOBReportValue(nType, nIndex, OD_PRICE);
                    varData[ORDER_ARGS_ODPRICE] = dODprice.ToString();

                    double dSTOPprice = axICETRADEAPI1.GetOBReportValue(nType, nIndex, STOP_PRICE);
                    varData[ORDER_ARGS_STOPPRICE] = dSTOPprice.ToString();
                    varData[ORDER_ARGS_MATCHQTY] = (int)axICETRADEAPI1.GetOBReportValue(nType, nIndex, DEAL_QTY); //成交口數                  

                    varData[ORDER_ARGS_ODKEY] = axICETRADEAPI1.GetOBReportString(nType, nIndex, ORDER_KEY);//此筆刪改單的key, 每次下單必須有一個unique的key                                   

                    varData[ORDER_ARGS_ID] = axICETRADEAPI1.GetOBReportString(nType, nIndex, FTR_ID);
                    varData[ORDER_ARGS_MTH] = axICETRADEAPI1.GetOBReportString(nType, nIndex, FTR_MTH);
                    varData[ORDER_ARGS_CP] = axICETRADEAPI1.GetOBReportString(nType, nIndex, CALLPUT);
                    varData[ORDER_ARGS_STRIKE] = axICETRADEAPI1.GetOBReportValue(nType, nIndex, STRIKE_PRICE);
                    varData[ORDER_ARGS_BS] = axICETRADEAPI1.GetOBReportString(nType, nIndex, BUYSELL);
                    varData[ORDER_ARGS_PRICE_FLAG] = axICETRADEAPI1.GetOBReportString(nType, nIndex, PRICE_FLAG);
                    varData[ORDER_ARGS_OPENCLOSE] = axICETRADEAPI1.GetOBReportString(nType, nIndex, OPENCLOSE);
                    varData[ORDER_ARGS_TRANSDATE] = axICETRADEAPI1.GetOBReportString(nType, nIndex, TRANS_DATE);
                    varData[ORDER_ARGS_EXCHANGE] = axICETRADEAPI1.GetOBReportString(nType, nIndex, EXCHANGE);
                    varData[ORDER_ARGS_DAYTRADE] = axICETRADEAPI1.GetOBReportString(nType, nIndex, DAY_TRADE);

                    object Data = varData;
                    int tmp = axICETRADEAPI1.ReduceOBFutOrder2(0, Data);
                    MessageBox.Show(tmp.ToString());
                }
            }
        }
    }
}
