<!-- 
Licensed to the Apache Software Foundation (ASF) under one
or more contributor license agreements.  See the NOTICE file
distributed with this work for additional information
regarding copyright ownership.  The ASF licenses this file
to you under the Apache License, Version 2.0 (the
"License"); you may not use this file except in compliance
with the License.  You may obtain a copy of the License at

  http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing,
software distributed under the License is distributed on an
"AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
KIND, either express or implied.  See the License for the
specific language governing permissions and limitations
under the License.
-->

# SHOW PARTITIONS
## description
    该语句用于展示分区信息
    语法：
        SHOW PARTITIONS FROM [db_name.]table_name [WHERE] [ORDER BY] [LIMIT];
    说明:
        支持PartitionId,PartitionName,State,Buckets,ReplicationNum,LastConsistencyCheckTime等列的过滤 

## example
    1.展示指定db下指定表的所有分区信息
        SHOW PARTITIONS FROM example_db.table_name;
        
    2.展示指定db下指定表的指定分区的信息
        SHOW PARTITIONS FROM example_db.table_name WHERE PartitionName = "p1";
    
    3.展示指定db下指定表的最新分区的信息        
        SHOW PARTITIONS FROM example_db.table_name ORDER BY PartitionId DESC LIMIT 1;
## keyword
    SHOW,PARTITIONS
