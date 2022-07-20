package com.application.easyteaching_harmony.data_structure;

import ohos.data.DatabaseHelper;
import ohos.data.orm.OrmContext;
import ohos.data.orm.OrmObject;
import ohos.data.orm.OrmPredicates;
import ohos.data.orm.annotation.Entity;
import ohos.data.orm.annotation.Index;
import ohos.data.orm.annotation.PrimaryKey;

import java.util.List;

@Entity(tableName = "students_information", ignoredColumns = {"ignoredColumn1", "ignoredColumn2"},
        indices = {@Index(value = {"name", "number", "scoring_rate"}, name = "name_index", unique = true)})
public class Students_Information extends OrmObject {
    @PrimaryKey(autoGenerate = true)
    private String name;//名字
    private int number;//号码
    private String scoring_rate;//得分率

    public String getName() {
        return name;
    }
    public void setName(String name) {
        this.name = name;
    }

    public int getNumber() {
        return number;
    }
    public void setNumber(int number) {
        this.number = number;
    }

    public String getScoring_rate() {
        return scoring_rate;
    }
    public void setScoring_rate(String scoring_rate) {
        this.scoring_rate = scoring_rate;
    }
}
