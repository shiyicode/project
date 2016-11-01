import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

/**
 * Created by shiyi on 16/8/30.
 */
public class MainFrame extends JFrame implements Runnable{

    JLabel lbIp, lbUser, lbPass, lbPort, lbD1, lbD2, lbNum;
    JTextField tfIp, tfUser, tfPass, tfPort, tfD1, tfD2, tfNum;
    JPanel jp1, jp2, jp3, jp4, jp5, jp6, jp7, jp;
    JButton jb;
    JTextArea jta;
    JScrollPane jsp;

    public void func() throws Exception {


    }

    public MainFrame() {

        jb = new JButton("开始合区");
        jb.setSize(20, 10);

        jb.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                Thread t = new Thread(MainFrame.this);
                t.start();
            }
        });

        jsp = new JScrollPane();
        jta = new JTextArea();
//        jsp.add(jta);

        jp = new JPanel();
        jp.setLayout(new FlowLayout());

        jp1 = new JPanel();
        jp2 = new JPanel();
        jp3 = new JPanel();
        jp4 = new JPanel();
        jp5 = new JPanel();
        jp6 = new JPanel();
        jp7 = new JPanel();

        jp.add(jp1);
        jp.add(jp2);
        jp.add(jp3);
        jp.add(jp4);
        jp.add(jp5);
        jp.add(jp6);
        jp.add(jp7);
        jp.add(jb);

        lbIp = new JLabel("服务器ip");
        lbUser = new JLabel("mysql用户名");
        lbPass = new JLabel("密码");
        lbPort = new JLabel("端口");
        lbD1 = new JLabel("主区数据库名");
        lbD2 = new JLabel("副区数据库名");
        lbNum = new JLabel("id增量");

        tfNum = new JTextField(20);
        tfIp = new JTextField(20);
        tfUser = new JTextField(20);
        tfPass = new JTextField(20);
        tfPort = new JTextField(20);
        tfD1 = new JTextField(20);
        tfD2 = new JTextField(20);
        tfUser.setText("root");
        tfPort.setText("3306");
        tfIp.setText("127.0.0.1");
        tfPass.setText("");
        tfD1.setText("");
        tfD2.setText("");

        jp1.add(lbIp);
        jp1.add(tfIp);
        jp2.add(lbUser);
        jp2.add(tfUser);
        jp3.add(lbPass);
        jp3.add(tfPass);
        jp4.add(lbPort);
        jp4.add(tfPort);
        jp5.add(lbD1);
        jp5.add(tfD1);
        jp6.add(lbD2);
        jp6.add(tfD2);
        jp7.add(lbNum);
        jp7.add(tfNum);

        this.setSize(350, 700);
        this.setLayout(new GridLayout(2, 1));
        this.add(jp);
        this.add(jta);

        this.setLocationRelativeTo(null);
        this.setResizable(false);
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        this.setVisible(true);
        this.setTitle("合区工具");
    }

    public static void main(String[] argc) {

        MainFrame f = new MainFrame();
    }

    @Override
    public void run() {
        String ip = tfIp.getText();
        String user = tfUser.getText();
        String port = tfPort.getText();
        String pass = tfPass.getText();
        String db1 = tfD1.getText();
        String db2 = tfD2.getText();
        String num = tfNum.getText();

        jta.setText("Begin\n");

        DBUtil db = new DBUtil(ip, user, port, pass, jta);
        db.openConnection();

        jta.append("db 连接成功\n");

        String sql = "use " + db2 + ";";
        jta.append(sql);
        //select database
        try {
            db.execCommand(sql);

//            jta.paintImmediately(jta.getBounds());

            jta.append("正在修改副区\n");

            db.execCommand("DROP TABLE IF EXISTS  arena_ladder_robot;");
            db.execCommand("DROP TABLE IF EXISTS lol_arena_robot;");
            db.execCommand("DROP TABLE IF EXISTS active_count;");
            db.execCommand("DROP TABLE IF EXISTS all_card_bucket;");
            db.execCommand("DROP TABLE IF EXISTS arena_ladder_rank;");
            db.execCommand("DROP TABLE IF EXISTS five_card_bucket;");
            db.execCommand("DROP TABLE IF EXISTS level_bucket;");
            db.execCommand("DROP TABLE IF EXISTS lol_arena_rank;");
            db.execCommand("DROP TABLE IF EXISTS global_data;");
            db.execCommand("DROP TABLE IF EXISTS server_logic_data;");
            db.execCommand("DROP TABLE IF EXISTS tower_bucket;");

            db.execCommand("update user set is_activity = is_activity - " + num + ";");

            //user_id
            db.execCommand("update all_card_ranklist set user_id = user_id + " + num + ";");
            db.execCommand("update arena_ladder_shop set user_id = user_id + " + num + ";");
            db.execCommand("update arena_ladder_user_info set userid = userid + " + num + ";");
            db.execCommand("update arena_ladder_combat_history set user_id = user_id + " + num + ";");
            db.execCommand("update battle_formation set user_id = user_id + " + num + ";");
            db.execCommand("update card set user_id = user_id + " + num + ";");
            db.execCommand("update challenge_daily_reward set user_id = user_id + " + num + ";");
            db.execCommand("update complete_quest set user_id = user_id + " + num + ";");
            db.execCommand("update courage_shop set user_id = user_id + " + num + ";");
            db.execCommand("update cross_arena_shop set user_id = user_id + " + num + ";");
            db.execCommand("update currency_shop set user_id = user_id + " + num + ";");
            db.execCommand("update daily_quest set user_id = user_id + " + num + ";");
            db.execCommand("update duplicate_data set user_id = user_id + " + num + ";");
            db.execCommand("update duplicate_reward set user_id = user_id + " + num + ";");
            db.execCommand("update epic_weappon_fresh set user_id = user_id + " + num + ";");
            db.execCommand("update epic_weappon_fresh_save set user_id = user_id + " + num + ";");
            db.execCommand("update five_card_ranklist set user_id = user_id + " + num + ";");
            db.execCommand("update flame_battle set user_id = user_id + " + num + ";");
            db.execCommand("update flame_battle_shop set user_id = user_id + " + num + ";");
            db.execCommand("update fort_friend set user_id = user_id + " + num + ";");
            db.execCommand("update friend set user_id = user_id + " + num + ";");
            db.execCommand("update friend_req set user_id = user_id + " + num + ";");
            db.execCommand("update goblin_shop set user_id = user_id + " + num + ";");
            db.execCommand("update guild_application set user_id = user_id + " + num + ";");
            db.execCommand("update guild_battle_user set user_id = user_id + " + num + ";");
            db.execCommand("update guild_dup_user_data set user_id = user_id + " + num + ";");
            db.execCommand("update guild_member set user_id = user_id + " + num + ";");
            db.execCommand("update headframes set user_id = user_id + " + num + ";");
            db.execCommand("update item_group set user_id = user_id + " + num + ";");
            db.execCommand("update level_ranklist set user_id = user_id + " + num + ";");
            db.execCommand("update life_skill_info set user_id = user_id + " + num + ";");
            db.execCommand("update life_skill_list set user_id = user_id + " + num + ";");
            db.execCommand("update lol_arena_combat_history set user_id = user_id + " + num + ";");
            db.execCommand("update lol_arena_formation set user_id = user_id + " + num + ";");
            db.execCommand("update lol_arena_shop set user_id = user_id + " + num + ";");
            db.execCommand("update lol_arena_user_info set userid = userid + " + num + ";");
            db.execCommand("update lottery_card set user_id = user_id + " + num + ";");
            db.execCommand("update lottery_card_discount set user_id = user_id + " + num + ";");

            db.execCommand("update mail set sender_id = sender_id + " + num + ";");
            db.execCommand("update mail set to_id = to_id + " + num + ";");

            db.execCommand("update manual set user_id = user_id + " + num + ";");
            db.execCommand("update new_life_skill set user_id = user_id + " + num + ";");
            db.execCommand("update orange_dupinfo set user_id = user_id + " + num + ";");
            db.execCommand("update orange_quest set user_id = user_id + " + num + ";");
            db.execCommand("update outland_data set user_id = user_id + " + num + ";");
            db.execCommand("update outland_shop set user_id = user_id + " + num + ";");
            db.execCommand("update pass_void_tower_team set pass_user_id = pass_user_id + " + num + ";");
            db.execCommand("update pole_boss_data set user_id = user_id + " + num + ";");

            db.execCommand("update quest set user_id = user_id + " + num + ";");
            db.execCommand("update secret_shop set user_id = user_id + " + num + ";");
            db.execCommand("update statistc_data set user_id = user_id + " + num + ";");
            db.execCommand("update sys_mail set to_id = to_id + " + num + ";");
            db.execCommand("update tencent_activity set user_id = user_id + " + num + ";");

            db.execCommand("update tencent_activity set user_id = user_id + " + num + ";");
            db.execCommand("update tencent_activity_bak set user_id = user_id + " + num + ";");
            db.execCommand("update tencent_activity_charge set user_id = user_id + " + num + ";");
            db.execCommand("update title set user_id = user_id + " + num + ";");
            db.execCommand("update tower_ranklist set user_id = user_id + " + num + ";");
            db.execCommand("update user set user_id = user_id + " + num + ";");
            db.execCommand("update user_challenge set user_id = user_id + " + num + ";");
            db.execCommand("update user_convoy_friend_info set user_id = user_id + " + num + ";");
            db.execCommand("update user_convoy_friend_info set friend_id = friend_id + " + num + ";");
            db.execCommand("update user_convoy_friend_reward set user_id = user_id + " + num + ";");
            db.execCommand("update user_convoy_info set user_id = user_id + " + num + ";");
            db.execCommand("update user_convoy_list set user_id = user_id + " + num + ";");
            db.execCommand("update user_convoy_list set friend_id = friend_id + " + num + ";");

            db.execCommand("update user_epic_weapon_protect set user_id = user_id + " + num + ";");
            db.execCommand("update user_epic_weapons set user_id = user_id + " + num + ";");
            db.execCommand("update user_ex set user_id = user_id + " + num + ";");
            db.execCommand("update user_fort_build set user_id = user_id + " + num + ";");
            db.execCommand("update user_fort_forge set user_id = user_id + " + num + ";");
            db.execCommand("update user_fort_gains set user_id = user_id + " + num + ";");
            db.execCommand("update user_holy_item set userid = userid + " + num + ";");
            db.execCommand("update void_rush set user_id = user_id + " + num + ";");
            db.execCommand("update void_tower set user_id = user_id + " + num + ";");
            db.execCommand("update mine_boss_data set user_id = user_id + " + num + ";");

            //record_id
            db.execCommand("update pass_void_tower_team set record_id = record_id + " + num + ";");


            // id   tencent_activity_bak
            db.execCommand("update tencent_activity_bak set id = id + " + num + ";");

            //sys_mail_id
            db.execCommand("update sys_mail set sys_mail_id = sys_mail_id + " + num + ";");

            //mail_id
            db.execCommand("update mail set mail_id = mail_id + " + num + ";");


            //guild_id
            db.execCommand("update guild set guild_id = guild_id + " + num + ";");
            db.execCommand("update guild_application set guild_id = guild_id + " + num + ";");
            db.execCommand("update guild_battle_list set guild_id = guild_id + " + num + ";");
            db.execCommand("update guild_battle_list set enemy_guild_id = enemy_guild_id + " + num + ";");
            db.execCommand("update guild_battle_record set guild_id = guild_id + " + num + ";");
            db.execCommand("update guild_dup_info set guild_id = guild_id + " + num + ";");
            db.execCommand("update guild_duplicate_distribute_info set guild_id = guild_id + " + num + ";");
            db.execCommand("update guild_member set guild_id = guild_id + " + num + " where guild_id != -1;");
            db.execCommand("update guild_tech set guild_id = guild_id + " + num + ";");
            db.execCommand("update guild_trench_info set guild_id = guild_id + " + num + ";");

            //chairman_id
            db.execCommand("update guild set chairman_id = chairman_id + " + num + ";");

            //qq_binder_user_id
            db.execCommand("update guild set qq_binder_user_id = qq_binder_user_id + " + num + " where qq_binder_user_id != -1;");


            //from_id
            db.execCommand("update friend_req set from_id = from_id + " + num + ";");

            //friend_id
            db.execCommand("update friend set friend_id = friend_id + " + num + ";");

            //card_id
            db.execCommand("update card_enhance_record set card_id = card_id + " + num + ";");
            db.execCommand("update card set card_id = card_id + " + num + ";");
            db.execCommand("update orange_quest set card_id = card_id + " + num + ";");


            db.execCommand("update lol_arena_formation set captain_id = captain_id + " + num + " where captain_id != -1;");
            db.execCommand("update lol_arena_formation set position_0 = position_0 + " + num + " where position_0 != -1;");
            db.execCommand("update lol_arena_formation set position_1 = position_1 + " + num + " where position_1 != -1;");
            db.execCommand("update lol_arena_formation set position_2 = position_2 + " + num + " where position_2 != -1;");
            db.execCommand("update lol_arena_formation set position_3 = position_3 + " + num + " where position_3 != -1;");
            db.execCommand("update lol_arena_formation set position_4 = position_4 + " + num + " where position_4 != -1;");
            db.execCommand("update lol_arena_formation set position_5 = position_5 + " + num + " where position_5 != -1;");
            db.execCommand("update lol_arena_formation set position_6 = position_6 + " + num + " where position_6 != -1;");
            db.execCommand("update lol_arena_formation set position_7 = position_7 + " + num + " where position_7 != -1;");


//        //weaponId???
//        db.execCommand("update complete_quest set user_id = user_id + " + num + "");


            jta.append("副区修改完成\n");

            jta.append("正在导出副区\n");

            String local;
            File directory = new File("");//设定为当前文件夹
            local = directory.getAbsolutePath();//获取绝对路径


            //window
            String cmd = String.format("%s\\tool\\mysqldump.exe -u%s -p%s -P %s -h %s --no-create-info %s > temp.sql",
                local, user, pass, port, ip, db2);

            File file=new File("export.bat");
            if(file.exists())
                file.delete();
            file.createNewFile();
            FileOutputStream out = new FileOutputStream(file, true);
            out.write(cmd.getBytes("utf-8"));
            out.close();

            System.out.println(cmd);
            Command.exeCmd(local + "\\export.bat");
            jta.append("副区导出完成\n");

            jta.append("正在将副区导入到主区\n");

//            db.execCommand("use " + db1);
//              db.execCommand(cmd);
            cmd = String.format("%s\\tool\\mysql.exe -f -u%s -p%s -P %s -h %s %s < temp.sql",
                    local, user, pass, port, ip, db1);

            file=new File("import.bat");
            if(file.exists())
                file.delete();
            file.createNewFile();
            out = new FileOutputStream(file, true);
            out.write(cmd.getBytes("utf-8"));
            out.close();

            System.out.println(cmd);
            Command.exeCmd(local + "\\import.bat");

                //linux
//            String cmd = String.format("/usr/local/mysql-5.7.12-osx10.11-x86_64/bin/mysqldump -u%s -p%s -h %s --skip-extended-insert --no-create-info %s > /Users/shiyi/temp.sql",
//                    user, pass, ip, db2);
//
//            File file=new File("export.sh");
//            if(file.exists())
//                file.delete();
//            file.createNewFile();
//            FileOutputStream out = new FileOutputStream(file, true);
//            out.write(cmd.getBytes("utf-8"));
//            out.close();
//            System.out.println(cmd);
//            Command.exeCmd("sh " + local + "/export.sh");
//            System.out.println("sh " + local + "/export.sh");
//            jta.append("副区导出完成\n");
//
//            jta.append("正在将副区导入到主区\n");
//
//            cmd = String.format("/usr/local/mysql-5.7.12-osx10.11-x86_64/bin/mysql -u%s -p%s -h %s -f %s < /Users/shiyi/temp.sql",
//                    user, pass, ip, db1);
//            file=new File("import.sh");
//            if(file.exists())
//                file.delete();
//            file.createNewFile();
//            out = new FileOutputStream(file, true);
//            out.write(cmd.getBytes("utf-8"));
//            out.close();
//
//            System.out.println(cmd);
//            System.out.println("sh " + local + "/import.sh");
//            Command.exeCmd("sh " + local + "/import.sh");

// linuxend

            jta.append("主副区合并完成\n");

            db.execCommand("use " + db1 + ";");
            db.execCommand("set @@sql_mode='STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION';");
            db.execCommand("delete from user where level < 10;");
            db.execCommand("DROP TABLE IF EXISTS  temp1;");
            db.execCommand("DROP TABLE IF EXISTS  temp2;");
            db.execCommand("create table temp1 as select level, user_id, open_id from user order by level;");
            db.execCommand("create table temp2 as select level, user_id, open_id from temp1 group by open_id having count(open_id) > 1;");
            db.execCommand("delete from user where user_id in (select user_id from temp2);");
            db.execCommand("update user set is_activity = 0;");

            jta.append("重复账号处理完成\n");


        } catch (Exception e) {
            e.printStackTrace();
            jta.append("error\n");
        }

        jta.append("End\n");

    }
}
