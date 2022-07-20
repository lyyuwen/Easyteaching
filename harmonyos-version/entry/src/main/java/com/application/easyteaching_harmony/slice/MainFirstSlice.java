package com.application.easyteaching_harmony.slice;

import com.application.easyteaching_harmony.ResourceTable;
//import com.application.easyteaching_harmony.tools.showList;
import ohos.aafwk.ability.fraction.Fraction;
import ohos.aafwk.content.Intent;
import ohos.agp.components.Component;
import ohos.agp.components.ComponentContainer;
import ohos.agp.components.LayoutScatter;
import ohos.agp.components.ListContainer;
import ohos.data.DatabaseHelper;
import ohos.hiviewdfx.HiLog;
import ohos.hiviewdfx.HiLogLabel;

import java.util.ArrayList;
import java.util.List;

public class MainFirstSlice extends Fraction {

    static final HiLogLabel label = new HiLogLabel(HiLog.LOG_APP, 0x00201, "MY_TAG");

    @Override
    protected Component onComponentAttached(LayoutScatter scatter, ComponentContainer container, Intent intent) {
        Component component = scatter.parse(ResourceTable.Layout_ability_main_first,container,false);
        ListContainer listContainer = (ListContainer) component.findComponentById(ResourceTable.Id_List_show_Data);
        //initListContainer(listContainer);
        return component;
    }
/*
    private void initListContainer(ListContainer listContainer) {
        List<Students_Information> list;
        showList sampleItemProvider = new showList(list, this,helper);
        listContainer.setItemProvider(sampleItemProvider);
        list.add(new Students_Information(helper));
        listContainer.setBindStateChangedListener(new Component.BindStateChangedListener() {
            @Override
            public void onComponentBoundToWindow(Component component) {
                // ListContainer初始化时数据统一在provider中创建，不直接调用这个接口；
                // 建议在onComponentBoundToWindow监听或者其他事件监听中调用。
                sampleItemProvider.notifyDataChanged();
            }

            @Override
            public void onComponentUnboundFromWindow(Component component) {}
        });
    }

 */
}
