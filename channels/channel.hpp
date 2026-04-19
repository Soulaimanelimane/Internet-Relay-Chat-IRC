/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimane <slimane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 21:37:16 by slimane           #+#    #+#             */
/*   Updated: 2026/04/16 09:53:05 by slimane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
#define CHANNEL_HPP


#include "../clients/client.hpp"

// class Client;

class Channel
{
	private:
		std::string             name;
		std::string             topic;
		std::string             setter_topic;
		std::vector<Client *>   members;
		std::vector<Client *>   ops;
		std::vector<Client *>   invited;
		bool                    invite_only;
		bool                    tp_rest;
		bool					nd_pss;
		std::string             password;
		long long               lim_membrs;
		size_t                  def_lim_members;

	public:
		Channel(Client &cls, std::string &channel_name);
		~Channel();
		Channel();

        std::string getname();
        void add_member(Client &cls);
        std::vector<Client*> &getmembers();
        void remove_member(Client &cls, Client &rmvr);
        void remove_operator(Client &cls);
        void invite_member(Client &host, Client &guest);
        void ft_topic(Client &cls, std::string &topic);
        void ft_topic(Client &cls);
        int ft_mode(Client &cls, std::string md , std::string args, std::vector<Client *> &clients);
        void add_member_to_operator(Client &cls, Client &oprtr);
		void ft_list_members(Client &cls);
        void ft_broadcast(Client &sender, std::string &msg);
        void ft_broadcast_all(std::string &msg);
        bool isUserInChannel(const std::string &nickname) const;
        std::vector<Client*> &get_ops();
		int     check_is_in(Client &rmvr, std::vector<Client *> &list);
		void    remove_itself(Client &cls);
		std::string &get_name();
		
		void set_password(std::string &key);
		std::string &get_pass();
		bool get_permession ();

		void set_name(std::string _name){name = _name;};
		int ft_atoi(std::string str);
		size_t size();

		void List_members(Client &cls);
};

#endif