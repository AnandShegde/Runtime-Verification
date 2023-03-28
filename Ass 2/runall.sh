./perform_RV.sh testcases/property1/simple_next.property testcases/property1/system1.input outputs/property1/system.verdict
./perform_RV.sh testcases/property2/simple_E.property testcases/property2/system1.input outputs/property2/system.verdict
./perform_RV.sh testcases/property3/until_or.property testcases/property3/system1.input outputs/property3/system.verdict

diff outputs/property1/system.verdict testcases/property1/system1.verdict
diff outputs/property2/system.verdict testcases/property2/system1.verdict
diff outputs/property3/system.verdict testcases/property3/system1.verdict