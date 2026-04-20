#!/bin/bash
echo "=== Test 1: Non-interactive with valid commands ==="
echo -e "/bin/ls\n/bin/pwd\n/bin/whoami" | ./shell 2>&1 | tail -1

echo ""
echo "=== Test 2: Error handling ==="
echo -e "invalid\n/bin/ls" | ./shell 2>&1 | head -2

echo ""
echo "=== Test 3: Empty lines ==="
echo -e "\n/bin/pwd\n" | ./shell 2>&1 | tail -1

echo ""
echo "=== Test 4: EOF handling ==="
echo "/bin/echo test" | ./shell 2>&1

echo ""
echo "All tests completed!"
