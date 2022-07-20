package com.application.easyteaching_harmony.data_structure;

import ohos.data.orm.OrmObject;
import ohos.data.orm.annotation.Entity;
import ohos.data.orm.annotation.Index;
import ohos.data.orm.annotation.PrimaryKey;

@Entity(tableName = "users", ignoredColumns = {"ignoredColumn1", "ignoredColumn2"},
        indices = {@Index(value = {"id", "keycode"}, name = "name_index", unique = true)})
public class Users extends OrmObject {
    @PrimaryKey(autoGenerate = true)
    private String id;//名字
    private String keycode;//密码

    public String getName() {
        return id;
    }
    public void setId(String name) {
        this.id = name;
    }

    public String getKeycode() {
        return keycode;
    }
    public void setKeycode(String keycode) {
        this.keycode = keycode;
    }
}
