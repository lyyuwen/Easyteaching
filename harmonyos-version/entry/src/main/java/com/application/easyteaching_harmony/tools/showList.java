package com.application.easyteaching_harmony.tools;

import com.application.easyteaching_harmony.ResourceTable;

import ohos.aafwk.ability.fraction.Fraction;
import ohos.agp.components.*;
import ohos.data.DatabaseHelper;

import java.util.List;
/*
public class showList extends BaseItemProvider {
    private List<Students_Information> list;
    private Fraction slice;
    private DatabaseHelper helper;
    public showList(List<Students_Information> list, Fraction slice,DatabaseHelper helper) {
        this.list = list;
        this.slice = slice;
        this.helper = helper;
    }

    @Override
    public int getCount() {
        return list == null ? 0 : list.size();
    }
    @Override
    public Object getItem(int position) {
        if (list != null && position >= 0 && position < list.size()){
            return list.get(position);
        }
        return null;
    }
    @Override
    public long getItemId(int position) {
        //可添加具体处理逻辑
        return position;
    }
    @Override
    public Component getComponent(int position, Component convertComponent, ComponentContainer componentContainer) {
        final Component cpt;
        if (convertComponent == null) {
            cpt = LayoutScatter.getInstance(slice).parse(ResourceTable.Layout_item_for_list, null, false);
        } else {
            cpt = convertComponent;
        }
        Students_Information Item = list.get(position);
        Text text = (Text) cpt.findComponentById(ResourceTable.Id_item_index);
        text.setText(Item.getName());
        return cpt;
    }
}

 */
