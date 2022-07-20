package com.application.easyteaching_harmony.slice;

import com.application.easyteaching_harmony.ResourceTable;
import com.application.easyteaching_harmony.data_structure.BookStore;
import com.application.easyteaching_harmony.data_structure.Users;
import ohos.aafwk.ability.AbilitySlice;
import ohos.aafwk.ability.fraction.Fraction;
import ohos.aafwk.ability.fraction.FractionAbility;
import ohos.aafwk.content.Intent;
import ohos.aafwk.content.Operation;
import ohos.agp.components.Component;
import ohos.agp.components.DirectionalLayout;
import ohos.data.DatabaseHelper;
import ohos.data.orm.OrmContext;
import ohos.data.orm.OrmPredicates;

import java.util.List;

public class MainAbilitySlice extends AbilitySlice {
    DirectionalLayout Main_frame;
    private DatabaseHelper helper = new DatabaseHelper(this);

    @Override
    public void onStart(Intent intent) {
        super.onStart(intent);
        super.setUIContent(ResourceTable.Layout_ability_main);
        switch_page();
        Main_frame = (DirectionalLayout) findComponentById(ResourceTable.Id_Main_Frame);

        OrmContext context = helper.getOrmContext("BookStore", "BookStore.db", BookStore.class);
        Users user = new Users();
        user.setId("Administrator");
        user.setKeycode("EasyTeaching");
        context.insert(user);
        context.flush();
    }

    private void switch_page() {
        Operation operation = new Intent.OperationBuilder().withDeviceId("")
                .withBundleName(getBundleName())
                .withAbilityName(".Tools")
                .build();
        Intent intent = new Intent();
        intent.setOperation(operation);

        Component to_First_page = findComponentById(ResourceTable.Id_First_page);
        Component to_Operate_page = findComponentById(ResourceTable.Id_Operate_page);
        Component to_History_page = findComponentById(ResourceTable.Id_History_page);
        Component to_Mine_page = findComponentById(ResourceTable.Id_Mine_page);

        Component to_Login_page = findComponentById(ResourceTable.Id_Login_First);

        to_First_page.setClickedListener(
                component -> setUI(new MainFirstSlice()));

        to_Operate_page.setClickedListener(
                component -> setUI(new MainOperateSlice()));

        to_History_page.setClickedListener(
                component -> setUI(new MainHistorySlice()));

        to_Mine_page.setClickedListener(
                component -> setUI(new MainMineSlice()));

        to_Login_page.setClickedListener(
                component -> startAbility(intent));
    }

    public void setUI(Fraction fraction){
        //清空DirectionalLayout内容
        Main_frame.removeAllComponents();
        //加载界面
        ((FractionAbility)getAbility()).getFractionManager().startFractionScheduler().add(ResourceTable.Id_Main_Frame,fraction).submit();
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
