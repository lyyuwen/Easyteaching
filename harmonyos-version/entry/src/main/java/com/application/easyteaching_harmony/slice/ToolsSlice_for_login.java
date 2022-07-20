package com.application.easyteaching_harmony.slice;

import com.application.easyteaching_harmony.ResourceTable;
import com.application.easyteaching_harmony.data_structure.BookStore;
import com.application.easyteaching_harmony.data_structure.Users;
import ohos.aafwk.ability.AbilitySlice;
import ohos.aafwk.content.Intent;
import ohos.aafwk.content.Operation;
import ohos.agp.components.Component;
import ohos.agp.components.TextField;
import ohos.agp.window.dialog.ToastDialog;
import ohos.data.DatabaseHelper;
import ohos.data.orm.OrmContext;
import ohos.data.orm.OrmPredicates;
import ohos.hiviewdfx.HiLogLabel;

import java.util.List;

public class ToolsSlice_for_login extends AbilitySlice {

    private DatabaseHelper helper = new DatabaseHelper(this);
    private static final HiLogLabel LABEL_LOG = new HiLogLabel(3, 0xD001100, "Demo");

    @Override
    public void onStart(Intent intent) {
        super.onStart(intent);
        super.setUIContent(ResourceTable.Layout_ability_tools);

        Operation operation = new Intent.OperationBuilder().withDeviceId("")
                .withBundleName(getBundleName())
                .withAbilityName("MainAbility")
                .build();
        Component login_button = findComponentById(ResourceTable.Id_Login_button);
        Intent intents = new Intent();
        intents.setOperation(operation);
        login_button.setClickedListener(component -> Login(intents));
    }

    private void Login(Intent intent) {
        TextField text_id = (TextField) findComponentById(ResourceTable.Id_Login_id);
        TextField text_keycode = (TextField) findComponentById(ResourceTable.Id_Login_keycode);
        String Login_id = text_id.getText();
        String Login_keycode = text_keycode.getText();

        OrmContext context = helper.getOrmContext("BookStore", "BookStore.db", BookStore.class);
        OrmPredicates query = context.where(Users.class).equalTo("id", Login_id);
        List<Users> users = context.query(query);
        ToastDialog MessageTips = new ToastDialog(this);
        MessageTips.setSize(100,30);
        if(!users.isEmpty()){
            if(users.contains(Login_keycode)){
                MessageTips.setText("登录成功");
                MessageTips.show();
                startAbility(intent);
            }
            else{
                MessageTips.setText("密码错误");
                MessageTips.show();
            }
        }
        else {
            MessageTips.setText("账号错误");
            MessageTips.show();
        }

    }

    @Override
    public void onActive() {
        super.onActive();
    }

    @Override
    public void onForeground(Intent intent) {
        super.onForeground(intent);
    }
}
