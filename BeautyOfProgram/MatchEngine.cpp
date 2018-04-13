#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <sstream>

using namespace std;

class order {
public:
    long long price;
    long long qty;
    long long filled;
    bool isBuy;
    bool isGfd;
    bool cancelled{false};
    string orderId;

    order(long long _price, long long _qty, bool _isBuy, bool _isGfd, string _orderId) {
        this->price = _price;
        this->qty = _qty;
        this->isBuy = _isBuy;
        this->isGfd = _isGfd;
        this->orderId = _orderId;
        this->filled = 0;
    }

    long long remain_qty() { return qty - filled; }
};

bool is_number(const string& s) {
    string::const_iterator it = s.begin();
    while (it != s.end() && isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

long count_space(const string& s) { return count(s.begin(), s.end(), ' '); }

string process_str(const string& str) {
    if (str.empty()) return "";
    size_t i = 0, j = str.size() - 1;
    while (i <= j && str[i] == ' ') i++;
    while (j >= 0 && str[j] == ' ') j--;
    if (i > j) return "";
    string result = "";
    for (size_t k = i; k <= j; k++) {
        if (str[k] == ' ' && result[result.size() - 1] == ' ') continue;
        result += str[k];
    }
    return result;
}

class match_system {
public:
    map<long long, vector<shared_ptr<order>>, greater<long long>> bidBook;
    map<long long, vector<shared_ptr<order>>> askBook;
    map<string, shared_ptr<order>> id2order;

    void trade() {
        string t1 = "", t2 = "", order_id = "", line = "", price_str = "", qty_str = "";
        stringstream ss;
        long long price = 0, qty = 0;
        while (getline(cin, line)) {
            if (line.empty()) continue;
            line = process_str(line);
            ss.clear();
            ss << line;
            ss >> t1;
            if (t1 == "BUY" || t1 == "SELL") {
                if (count_space(line) == 4) {
                    ss >> t2 >> price_str >> qty_str >> order_id;
                    if (is_number(price_str) && is_number(qty_str) && (t2 == "GFD" || t2 == "IOC")) {
                        ss.clear();
                        ss << price_str << " " << qty_str;
                        ss >> price >> qty;
                        add_order(make_shared<order>(price, qty, t1 == "BUY", t2 == "GFD", order_id));
                    }
                }
            } else if (t1 == "CANCEL") {
                if (count_space(line) == 1) {
                    ss >> order_id;
                    cancel_order_soft(order_id);
                }
            } else if (t1 == "PRINT") {
                if (count_space(line) == 0) {
                    print_book();
                }
            } else if (t1 == "MODIFY") {
                if (count_space(line) == 4) {
                    ss >> order_id >> t2 >> price_str >> qty_str;
                    if (is_number(price_str) && is_number(qty_str) && (t2 == "BUY" || t2 == "SELL")) {
                        ss.clear();
                        ss << price_str << " " << qty_str;
                        ss >> price >> qty;

                        auto o = make_shared<order>(price, qty, t2 == "BUY", true, order_id);
                        if (cancel_order_hard(o)) {
                            add_order(o);
                        }
                    }
                }
            }
        }
    }

    void simulate() {
        add_order(make_shared<order>(10, 10, true, true, "order1"));
        add_order(make_shared<order>(9, 10, true, true, "order2"));
        add_order(make_shared<order>(11, 10, true, true, "order3"));
        add_order(make_shared<order>(10, 10, true, true, "order4"));
        add_order(make_shared<order>(20, 10, false, true, "order5"));
        add_order(make_shared<order>(19, 10, false, true, "order6"));
        add_order(make_shared<order>(21, 10, false, true, "order7"));
        add_order(make_shared<order>(20, 10, false, true, "order8"));
        print_book();
        add_order(make_shared<order>(10, 22, false, false, "order9"));
        cancel_order_soft("order4");
        cancel_order_soft("order1");
        print_book();
    }

    bool cancel_order_soft(string id) {
        auto itr = id2order.find(id);
        if (itr != id2order.end()) {
            itr->second->cancelled = true;
            return true;
        }
        return false;
    }

    bool cancel_order_hard(shared_ptr<order> o) {
        auto itr = id2order.find(o->orderId);
        if (itr != id2order.end() && !itr->second->cancelled) {
            if (id2order[o->orderId]->isBuy) {
                auto itr1 = find_if(bidBook[o->price].begin(), bidBook[o->price].end(),
                                    [o](shared_ptr<order>& order) { return order->orderId == o->orderId; });
                bidBook[o->price].erase(itr1);
            } else {
                auto itr1 = find_if(askBook[o->price].begin(), askBook[o->price].end(),
                                    [o](shared_ptr<order>& order) { return order->orderId == o->orderId; });
                askBook[o->price].erase(itr1);
            }
            id2order.erase(o->orderId);
            return true;
        }
        return false;
    }

    void print_book() {
        cout << "SELL:" << endl;
        for (auto itr = askBook.rbegin(); itr != askBook.rend(); ++itr) {
            long long q = 0;
            for (auto& o : itr->second) {
                if (!o->cancelled) {
                    q += o->remain_qty();
                }
            }
            if (q > 0) cout << itr->first << " " << q << endl;
        }

        cout << "BUY:" << endl;
        for (auto itr = bidBook.begin(); itr != bidBook.end(); ++itr) {
            long long q = 0;
            for (auto& o : itr->second) {
                if (!o->cancelled) {
                    q += o->remain_qty();
                }
            }
            if (q > 0) cout << itr->first << " " << q << endl;
        }
    }

    void add_order(shared_ptr<order> o) {
        long long fill_count = 0;
        if (o->price > 0 && o->qty > 0) {
            if (o->isBuy) {
                auto mapItr = askBook.begin();
                while (o->remain_qty() > 0 && mapItr != askBook.end()) {
                    if (mapItr->first <= o->price) {
                        auto vectorItr = mapItr->second.begin();
                        for (; vectorItr != mapItr->second.end(); ++vectorItr) {
                            order& askOrder = *(*vectorItr);
                            if (!askOrder.cancelled) {
                                if (askOrder.remain_qty() >= o->remain_qty()) {
                                    fill_count = o->remain_qty();
                                } else {
                                    fill_count = askOrder.remain_qty();
                                }
                                print_trade(askOrder, *o, fill_count);
                            }
                        }
                        if (vectorItr != mapItr->second.end() && (*vectorItr)->remain_qty() == 0) {
                            ++vectorItr;
                        }
                        remove_order(mapItr->second, vectorItr);
                    } else {
                        break;
                    }
                    ++mapItr;
                }  // end while
                if (mapItr != askBook.end() && mapItr->second.empty()) {
                    ++mapItr;
                }
                askBook.erase(askBook.begin(), mapItr);

                if (o->remain_qty() > 0 && o->isGfd) {
                    add_buy_list(o);
                }
            } else {  // sell
                auto mapItr = bidBook.begin();
                while (o->remain_qty() > 0 && mapItr != bidBook.end()) {
                    if (mapItr->first >= o->price) {
                        auto vectorItr = mapItr->second.begin();
                        for (; vectorItr != mapItr->second.end(); ++vectorItr) {
                            order& bidOrder = *(*vectorItr);
                            if (!bidOrder.cancelled) {
                                if ((*vectorItr)->remain_qty() >= o->remain_qty()) {
                                    fill_count = o->remain_qty();
                                } else {
                                    fill_count = (*vectorItr)->remain_qty();
                                }
                                print_trade(*(*vectorItr), *o, fill_count);
                            }
                        }
                        if (vectorItr != mapItr->second.end() && (*vectorItr)->remain_qty() == 0) {
                            ++vectorItr;
                        }
                        remove_order(mapItr->second, vectorItr);
                    } else {
                        break;
                    }
                    ++mapItr;
                }  // end while
                if (mapItr != bidBook.end() && mapItr->second.empty()) {
                    ++mapItr;
                }
                bidBook.erase(bidBook.begin(), mapItr);

                if (o->remain_qty() > 0 && o->isGfd) {
                    add_sell_list(o);
                }
            }
        }
    }

    void remove_order(vector<shared_ptr<order>>& orders, vector<shared_ptr<order>>::iterator itr1) {
        for (auto i = orders.begin(); i != itr1; ++i) {
            id2order.erase((*i)->orderId);
        }
        orders.erase(orders.begin(), itr1);
    }

    void add_buy_list(shared_ptr<order> o) {
        bidBook[o->price].push_back(o);
        id2order[o->orderId] = o;
    }

    void add_sell_list(shared_ptr<order> o) {
        askBook[o->price].push_back(o);
        id2order[o->orderId] = o;
    }

    /**
     * @param o1 old order
     * @param o2 new order
     * @param count
     */
    void print_trade(order& o1, order& o2, long long count) {
        cout << "TRADE " << o1.orderId << " " << o1.price << " " << count << " " << o2.orderId << " " << o2.price << " "
             << count << endl;
        o2.filled += count;
        o1.filled += count;
    }
};

int main() {
    match_system s;
    s.simulate();
    //    s.trade();
    return 0;
}
